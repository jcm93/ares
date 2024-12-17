#pragma once

#include <AudioToolbox/AudioToolbox.h>

void coreAudioCallback(void *userData, AudioQueueRef queue, AudioQueueBufferRef buffer);
void coreAudioBufferFinishedPlaying(void *userData, AudioQueueRef queue, AudioQueuePropertyID prop);
struct AudioCoreAudio;

