// TODO: NOT IN USE


#include "ctap.h"



int main(void) {

/*
    int j;
    for(j = 1; j < i; j++) {
      int note = strtol(words[j], NULL, 0);
      switch (note) {
        case 1: play_sound("../wavs/piano/c1.wav"); break;
        case 2: play_sound("../wavs/piano/d1.wav"); break;
        case 3: play_sound("../wavs/piano/e1.wav"); break;
        default:
                SDL_Delay(strtol(words[0], NULL, 0));
      }
    }
*/

  int num_lines = count_lines("music.txt");
  char** words = read_file("music.txt");



  int j;
  for(j = 1; j < num_lines; j++) {
    int two_note = strtol(words[j], NULL, 0);
    int button   = two_note / 10;
    int track    = two_note % 10;
    SDL_Delay(strtol(words[0], NULL, 0));
    switch (button) {
      case 1: printf("Button: %d Track: %d\n", button, track); break;
      case 2: printf("Button: %d Track: %d\n", button, track); break;
      case 3: printf("Button: %d Track: %d\n", button, track); break;
      default:
              printf("%s \n", "Delay");
              SDL_Delay(strtol(words[0], NULL, 0));
    }
  }
}
