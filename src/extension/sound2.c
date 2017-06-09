#include "sound.h"

int main(int argc, char *argv[]) {
  printf("%s\n", "Press a 1 or 2 or 3 for respective sounds");
  char s[2];
  scanf("%s", s);
  /*if (s[0] != '1' | s[0] != '2' | s[0] != '3') {
    printf("%s\n", "Wrong number, try again!");
    return -1;
  } */
  int s_int = strtol(s, NULL, 10);
  switch (s_int) {
    case 1: play_sound("../1.wav", 600); break;
    case 2: play_sound("../2.wav", 600); break;
    case 3: play_sound("../3.wav", 600); break; 
  }
  return 0;
}
