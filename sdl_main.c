#include "SDL2/SDL_audio.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#include "sounds.h"
#include "build/sounds/dzin.h"
#include "build/sounds/bump.h"
#include "build/sounds/hi.h"

const int SAMPLE_RATE = 8000;
const int BUFFER_SIZE = 8000;

int main() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
    printf("Failed to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_AudioSpec spec = {
      .format = AUDIO_U8,
      .channels = 1,
      .freq = SAMPLE_RATE,
      .samples = BUFFER_SIZE,
      .callback = NULL,
  };

SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);

SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_HI.start, SOUND_HI.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_HI.start, SOUND_HI.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_BUMP.start, SOUND_BUMP.length);
SDL_QueueAudio(deviceId, SOUND_DZIN.start, SOUND_DZIN.length);
SDL_QueueAudio(deviceId, SOUND_HI.start, SOUND_HI.length);
SDL_PauseAudioDevice(deviceId, 0);

  while (1) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
          case SDL_QUIT:
            return 0;
      }
    }
  }

  return 0;
}
