#include "extension.h"

void play_sound(char* wav_file_name, int time) {

  Mix_Chunk *sound = NULL;
  int channel;

  // 22050 is a good frequency value to use
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16SYS;
  int audio_channels = 2;
  int audio_buffers = 4096;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
  }
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
    printf("Unable to initialize audio: %s\n", Mix_GetError());
    exit(1);
  }

  sound = Mix_LoadWAV(wav_file_name);
  if(sound == NULL) {
    printf("Unable to load WAV file: %s\n", Mix_GetError());
  }

  channel = Mix_PlayChannelTimed(-1, sound, 0, time);
  if(channel == -1) {
    printf("Unable to play WAV file: %s\n", Mix_GetError());
  }

  // TODO: NEED TO DO THIS
  //Mix_FreeChunk(sound);
  //Mix_CloseAudio();
  //SDL_Quit();

}
