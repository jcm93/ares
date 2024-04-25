#include <AVFAudio/AVAudioEngine.h>
#include <AVFoundation/AVAudioPlayerNode.h>
#include <AVFoundation/AVAudioTypes.h>
#include <AVFoundation/AVAudioMixerNode.h>

struct AudioAVAE : AudioDriver {
  AudioAVAE& self = *this;
  AudioAVAE(Audio& super) : AudioDriver(super) {}
  ~AudioAVAE() { terminate(); }
  
  AVAudioFormat *format = nil;
  AVAudioEngine *audioEngine = nullptr;
  AVAudioPlayerNode *playerNode = nullptr;

  auto create() -> bool override {
    super.setChannels(2);
    super.setFrequency(44100);
    super.setLatency(20);
    return initialize();
  }

  auto driver() -> string override { return "AVAudioEngine"; }
  auto ready() -> bool override { return _ready; }

  auto hasBlocking() -> bool override { return true; }
  auto hasDynamic() -> bool override { return false; }

  auto hasFrequencies() -> vector<u32> override {
    return {44100, 48000, 96000};
  }

  auto hasLatencies() -> vector<u32> override {
    return {10, 20, 40, 60, 80, 100};
  }

  auto setFrequency(u32 frequency) -> bool override { return initialize(); }
  auto setLatency(u32 latency) -> bool override { return initialize(); }
  auto setBlocking(bool blocking) -> bool override { clear(); return true; }

  auto clear() -> void override {
    if(!ready()) return;
  }

  auto output(const f64 samples[]) -> void override {
    if(!ready()) return;

    std::unique_ptr<f32[]> output = std::make_unique<f32[]>(channels);
    for(auto n : range(channels)) output[n] = samples[n];
    //uhhhhhhh
    size_t bufferSize = sizeof(output) / sizeof(float);
    AudioBufferList abl;
    abl.mNumberBuffers = 1;
    abl.mBuffers[0].mData = &output;
    abl.mBuffers[0].mNumberChannels = 1;
    abl.mBuffers[0].mDataByteSize = bufferSize;
    AVAudioPCMBuffer *buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:format bufferListNoCopy:&abl deallocator:NULL];
    [playerNode scheduleBuffer:buffer completionHandler:nil];
  }

  auto level() -> f64 override {
  }

private:
  auto initialize() -> bool {
    terminate();
    
    format = [[AVAudioFormat alloc] initStandardFormatWithSampleRate:self.frequency channels:2];
    
    NSError *error = nil;
    
    audioEngine = [[AVAudioEngine alloc] init];
    playerNode = [[AVAudioPlayerNode alloc] init];
    [audioEngine attachNode:playerNode];
    [audioEngine connect:playerNode to:audioEngine.mainMixerNode format:format];
    [audioEngine prepare];
    [audioEngine startAndReturnError:&error];
    _ready = true;
    clear();

    return true;
  }

  auto terminate() -> void {
    [audioEngine stop];
    _ready = false;
    audioEngine = nil;
    playerNode = nil;
  }

  bool _ready = false;
  
  u32 _bufferSize = 0;
};

