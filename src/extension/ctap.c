#include "ctap.h"

int main(int argc, char *argv[]) {

  // Initialise Gtk
  gtk_init(&argc, &argv);

  // Create the main program struct which will be passed around the program
  ctap_t *game = malloc(sizeof(ctap_t));

  // Initialise the game
  init_window(game);
  init_container(game);
  init_startscreen(game);
  init_buttons(game);


  char** words = read_file("music.txt");
  int num_lines = count_lines("music.txt");
  for (int i = 0; i < num_lines; i++) {
    printf("%s\n", words[i]);
  }


  // Start the main loop
  gtk_main();

  // Free the game
  free(game);

  return 0;

}
