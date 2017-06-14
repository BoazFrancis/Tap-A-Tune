#include "ctap.h"

void start_song(ctap_t *game) {

  int playing_song = 0;
  int note_number = 0;
  char *filename = "music.txt";
  char **words = read_file(filename);
  int num_lines = count_lines(filename);
  for (int i = 0; i < num_lines; i++) {

    // To lower case
    words[i] = str_lower(words[i]);
    words[i] = trim_whitespace(words[i]);

    // Ignore comments
    if (words[i][0] == '#') {
      continue;
    }

    // Ignore empty lines
    if (strcmp(words[i], "") == 0) {
      continue;
    }

    // Set speed and tempo
    char *value, *keyword;
    keyword = strtok_r(words[i], " ", &value);
    if (strcmp(keyword, "speed") == 0) {
      game->speed = strtol(trim_whitespace(value), NULL, 0);
      continue;
    }
    else if (strcmp(keyword, "tempo") == 0) {
      game->tempo = strtol(trim_whitespace(value), NULL, 0);
      continue;
    }

    // Start and end song
    if (strcmp(words[i], "begin") == 0) {
      playing_song = 1;
      continue;
    }
    else if (strcmp(words[i], "end") == 0) {
      playing_song = 0;
      continue;
    }

    // Get notes
    if (playing_song == 1) {
      int note = words[i][0];
      GObject *params = g_object_new(G_TYPE_OBJECT, NULL);
      g_object_set_data(params, "game", game);
      g_object_set_data(params, "note", GINT_TO_POINTER(note));
      g_timeout_add(game->tempo * note_number, create_note, params);
      note_number++;
    }

  }

}
