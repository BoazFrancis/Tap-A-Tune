#include "ctap.h"

int main(int argc, char *argv[]) {

  // Initialise Gtk
  gtk_init(&argc, &argv);

  // Create the main program struct which will be passed around the program
  ctap_t *game = malloc(sizeof(ctap_t));

  // Initialise the game
  init_notetable(game);
  init_window(game);
  init_container(game);
  init_startscreen(game);
  init_buttons(game);


  // Start the main loop
  gtk_main();

  // Free game struct attributes
  free(game->buttons);
  free(game->dots);
  free(game->map);
  // Free the game
  free(game);

  return 0;

}
