#include "ctap.h"
#include <libgen.h>

int main(int argc, char *argv[]) {

  // Initialise Gtk
  gtk_init(&argc, &argv);

  // Create the main program struct which will be passed around the program
  ctap_t *game = malloc(sizeof(ctap_t));

  if (game == NULL) {
    perror("game malloc in ctap");
    exit(EXIT_FAILURE);
  }

  game->path = dirname(argv[0]);

  // Initialise the game
  init_notetable(game);
  init_window(game);
  init_container(game);
  init_startscreen(game);
  init_buttons(game);


  // Start the main loop
  gtk_main();

  free(game);

  return 0;

}
