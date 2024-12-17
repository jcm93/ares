#include "coreaudio.hpp"

struct AudioCoreAudio : AudioDriver {
  AudioCoreAudio& self = *this;
  AudioCoreAudio(Audio& super) : AudioDriver(super) {}
  ~AudioCoreAudio() { terminate(); }
  
  auto create() -> bool override {
    super.setChannels(2);
    super.setFrequency(48000);
    super.setLatency(20);
    return initialize();
  }
  
  auto driver() -> string override { return "CoreAudio"; }
  auto ready() -> bool override { return _ready; }

  auto hasBlocking() -> bool override { return true; }
  auto hasDynamic() -> bool override { return true; }

  auto hasFrequencies() -> vector<u32> override {
    return {44100, 48000, 96000};
  }

  auto hasLatencies() -> vector<u32> override {
    return {10, 20, 40, 60, 80, 100};
  }

  auto setFrequency(u32 frequency) -> bool override { return initialize(); }
  auto setLatency(u32 latency) -> bool override { return initialize(); }
  auto setBlocking(bool blocking) -> bool override { clear(); return true; }
  
  auto output(const f64 samples[]) -> void override {
    if (!ready()) return;
    
    if (self.blocking) {
      unique_lock<mutex> lock(_audioBufferMutex);
      _audioCondition.wait(lock, [&] { return _readyForMoreAudio.load(); });
    }
    
    AudioQueueBufferRef buffer = _audioQueueBuffers[_bufferIndex];
    u32 bufferFrameCapacity = buffer->mAudioDataBytesCapacity / _format.mBytesPerFrame;
    f64 *bufferData = (f64 *)buffer->mAudioData;
    bufferData[_currentBufferSamples] = samples[0];
    bufferData[_currentBufferSamples + 1] = samples[1];
    _currentBufferSamples += 2;

    if (self.blocking) {
      if (_currentBufferSamples >= _sampleBlockInterval) {
        auto microsecondsToSleep = ((f64)_sampleBlockInterval / _format.mSampleRate) * 1000;
        usleep(microsecondsToSleep);
      }
    }
    
    if (_currentBufferSamples > bufferFrameCapacity) {
      buffer->mAudioDataByteSize = bufferFrameCapacity * _format.mBytesPerFrame;
      AudioQueueEnqueueBuffer(_coreAudioQueue, _audioQueueBuffers[_bufferIndex], 0, 0);
      _currentBufferSamples = 0;
      _readyForMoreAudio = false;
    }
  }
  
  u32 _bufferIndex = 0;
  mutex _audioBufferMutex;
  condition_variable _audioCondition;
  atomic<bool> _readyForMoreAudio = false;
  
private:
  
  auto initialize() -> bool {
    terminate();
    
    AudioStreamBasicDescription format = {0};
    
    format.mFormatID = kAudioFormatLinearPCM;
    format.mSampleRate = (f64)frequency;
    format.mChannelsPerFrame = 2;
    format.mFormatFlags = (kAudioFormatFlagIsFloat);
    format.mBitsPerChannel = 64;
    format.mChannelsPerFrame = 2;
    format.mFramesPerPacket = 1;
    format.mBytesPerFrame = format.mBitsPerChannel / 8 * format.mChannelsPerFrame;
    format.mBytesPerPacket = format.mBytesPerFrame * format.mFramesPerPacket;
    
    _format = format;
    
    AudioQueueNewOutput(&format, &coreAudioCallback, &self, 0, 0, 0, &_coreAudioQueue);
    
    int bufferSize = format.mBytesPerFrame * (format.mSampleRate * ((f64)self.latency / (f64)1000));
    
    OSStatus err;
    err = AudioQueueAllocateBuffer(_coreAudioQueue, bufferSize, &(_audioQueueBuffers[0]));
    assert(!err);
    err = AudioQueueAllocateBuffer(_coreAudioQueue, bufferSize, &(_audioQueueBuffers[1]));
    assert(!err);
  
    _ready = true;
    
    coreAudioCallback(&self, _coreAudioQueue, _audioQueueBuffers[0]);
    coreAudioCallback(&self, _coreAudioQueue, _audioQueueBuffers[1]);
    
    err = AudioQueueStart(_coreAudioQueue, 0);
    assert(!err);

    return true;
  }
  
  
  auto terminate() -> void {
    AudioQueueDispose(_coreAudioQueue, YES);
    _ready = false;
  }
  
  AudioStreamBasicDescription _format;
  AudioQueueBufferRef _audioQueueBuffers[2];
  AudioQueueRef _coreAudioQueue;
  bool _ready = false;
  u32 _currentBufferSamples = 0;
  u32 _sampleBlockInterval = 50;
};

void coreAudioCallback(void *userData, AudioQueueRef queue, AudioQueueBufferRef buffer) {
  AudioCoreAudio *audio = (AudioCoreAudio *)userData;
  audio->_bufferIndex ^= 1;
  audio->_readyForMoreAudio = true;
  audio->_audioCondition.notify_one();
}
