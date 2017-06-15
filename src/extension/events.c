#include "ctap.h"

void start_game(GtkWidget *window, GdkEventKey *event, gpointer user_data) {

  if (event->keyval == ENTER_KEY) {

    ctap_t *game = user_data;

    gtk_container_remove(GTK_CONTAINER(game->container), game->content);

    // Draw lines and buttons
    draw_lines(game);
    draw_buttons(game);
    gtk_widget_show_all(game->window);

    init_score(game);
    // Don't care about this key press event anymore
    gtk_signal_disconnect_by_func(GTK_OBJECT(game->window), GTK_SIGNAL_FUNC(start_game), user_data);

    // Key presses for 5 different buttons
    g_signal_connect(game->window, "key-press-event", G_CALLBACK(select_button), game);
    g_signal_connect(game->window, "key-release-event", G_CALLBACK(release_button), game);

    start_song(game);

  }

}

void select_button(GtkWidget *window, GdkEventKey *event, gpointer user_data) {

  ctap_t *game = user_data;
  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  char *label;

  switch (event->keyval) {
    case RED_KEY:     label = RED_LABEL; break;
    case BLUE_KEY:    label = BLUE_LABEL; break;
    case GREEN_KEY:   label = GREEN_LABEL; break;
    case YELLOW_KEY:  label = YELLOW_LABEL; break;
    case PURPLE_KEY:  label = PURPLE_LABEL; break;
    default: return;
  }

  for (int i=0; i<game->num_buttons; i++) {
    if (strcmp(game->buttons[i].key, label) == 0 && game->buttons[i].is_selected == 0) {
      // Highlight the button
      gtk_fixed_put(GTK_FIXED(game->container), game->buttons[i].selected, BUTTONS_XOFFSET + i*BUTTONS_XINC, height-BUTTONS_YOFFSET);
      g_object_ref(game->buttons[i].selected);
      game->buttons[i].is_selected = 1;
    }
  }

  gtk_widget_show_all(window);

}

void release_button(GtkWidget *window, GdkEventKey *event, gpointer user_data) {

  ctap_t *game = user_data;

  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  for (int i=0; i<game->num_buttons; i++) {
    if (game->buttons[i].is_selected == 1) {

      gtk_container_remove(GTK_CONTAINER(game->container), game->buttons[i].selected);
      game->buttons[i].is_selected = 0;

      // Check if any dots on this track are selectable
      for (int j=0; j<game->num_dots; j++) {
        if (game->dots[j].track == i) {
          // If in boundary to press
          int total_distance = (height-BUTTONS_YOFFSET);
          if (game->dots[j].y >= total_distance - BUTTON_BOUNDARY && game->dots[j].y <= total_distance + BUTTON_BOUNDARY) {
            // Play the sound
            char *sound_file = malloc(sizeof(char)*12);
            sprintf(sound_file, "wav/%c1.wav", game->dots[j].note);
            play_sound(sound_file, -1);
          }
        }
      }

    }
  }

  gtk_widget_show_all(game->window);

}

gboolean move_dot(gpointer user_data) {

  GObject *params = user_data;
  ctap_t *game = g_object_get_data(params, "game");
  int track = GPOINTER_TO_INT(g_object_get_data(params, "track"));

  game->dots[track].y++;
  gtk_fixed_move(GTK_FIXED(game->container), game->dots[track].widget, game->dots[track].x, game->dots[track].y);

  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);

  return FALSE;

}

gboolean create_note(gpointer user_data) {

  GObject *params = user_data;
  ctap_t *game = g_object_get_data(params, "game");
  char note = GPOINTER_TO_INT(g_object_get_data(params, "note"));

  draw_dot(game, note);

  gtk_widget_show_all(game->window);

  return FALSE;

}
