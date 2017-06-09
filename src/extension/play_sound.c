#include "sound.h"

void play_sound(char* wav_file_name, int time) {
  //SDL_Surface *screen;
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


  /*screen = SDL_SetVideoMode(320, 240, 0, SDL_ANYFORMAT);
  if (screen == NULL) {
          printf("Unable to set video mode: %s\n", SDL_GetError());
          return 1;
  }*/


  channel = Mix_PlayChannelTimed(-1, sound, 0, time);
  if(channel == -1) {
    printf("Unable to play WAV file: %s\n", Mix_GetError());
  }
  while(Mix_Playing(channel) != 0);

  /*
  printf("%s\n", "Press 'a' to play bell sound");
  char button;
  scanf("%c", &button);
  if (button == 'a') {
    printf("%s\n", "a" );
    channel = Mix_PlayChannel(-1, sound, 0);
    if(channel == -1) {
      printf("Unable to play WAV file: %s\n", Mix_GetError());
    }
    while(Mix_Playing(channel) != 0);
  } */
  Mix_FreeChunk(sound);
  Mix_CloseAudio();
  SDL_Quit();
}



void play2sounds(char* wav_file_name1, char* wav_file_name2) {
  //SDL_Surface *screen;
  Mix_Chunk *sound1 = NULL;
  Mix_Chunk *sound2 = NULL;

  int channel1, channel2;

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

  sound1 = Mix_LoadWAV(wav_file_name1);
  if(sound1 == NULL) {
    printf("Unable to load WAV file: %s\n", Mix_GetError());
  }

  sound2 = Mix_LoadWAV(wav_file_name2);
  if(sound2 == NULL) {
    printf("Unable to load WAV file: %s\n", Mix_GetError());
  }



  channel1 = Mix_PlayChannel(0, sound1, 0);
  if(channel1 == -1) {
    printf("Unable to play WAV file: %s\n", Mix_GetError());
  }
  while(Mix_Playing(channel1) != 0);

  channel2 = Mix_PlayChannel(1, sound2, 0);
  if(channel2 == -1) {
    printf("Unable to play WAV file: %s\n", Mix_GetError());
  }
  while(Mix_Playing(channel2) != 0);

  Mix_FreeChunk(sound1);
  Mix_FreeChunk(sound2);
  Mix_CloseAudio();
  SDL_Quit();
}
