#include "ctap.h"

void start_game(GtkWidget *window, GdkEventKey *event, gpointer user_data) {

  if (event->keyval == ENTER_KEY) {

    ctap_t *game = user_data;

    // Get screen height
    gtk_window_get_size(GTK_WINDOW(game->window), NULL, &game->max_height);

    gtk_container_remove(GTK_CONTAINER(game->container), game->content);

    // Draw lines and buttons
    init_lines(game);
    draw_buttons(game);
    gtk_widget_show_all(game->window);

    init_score(game);

    draw_escape(game);
    // Disconnect key press event
    gtk_signal_disconnect_by_func(GTK_OBJECT(game->window), GTK_SIGNAL_FUNC(start_game), user_data);

    // Key presses for 5 different buttons
    g_signal_connect(game->window, "key-press-event", G_CALLBACK(select_button), game);
    g_signal_connect(game->window, "key-release-event", G_CALLBACK(release_button), game);

    start_song(game);

  }
  else if (event->keyval == ESC_KEY) {
    gtk_main_quit();
  }

}

void select_button(GtkWidget *window, GdkEventKey *event, gpointer user_data) {

  ctap_t *game = user_data;
  char *label;

  switch (event->keyval) {
    case RED_KEY:     label = RED_LABEL; break;
    case BLUE_KEY:    label = BLUE_LABEL; break;
    case GREEN_KEY:   label = GREEN_LABEL; break;
    case YELLOW_KEY:  label = YELLOW_LABEL; break;
    case PURPLE_KEY:  label = PURPLE_LABEL; break;
    case ESC_KEY:     gtk_main_quit(); return;
    default: return;
  }

  for (int i=0; i<game->num_buttons; i++) {
    if (strcmp(game->buttons[i].key, label) == 0 && game->buttons[i].is_selected == 0) {
      // Highlight the button
      gtk_fixed_put(GTK_FIXED(game->container), game->buttons[i].selected, BUTTONS_XOFFSET + i*BUTTONS_XINC, game->max_height-BUTTONS_YOFFSET);
      g_object_ref(game->buttons[i].selected);
      game->buttons[i].is_selected = 1;
    }
  }

  gtk_widget_show_all(window);

}

void release_button(GtkWidget *window, GdkEventKey *event, gpointer user_data) {

  ctap_t *game = user_data;

  for (int i=0; i<game->num_buttons; i++) {
    int within_range = 0;
    if (game->buttons[i].is_selected == 1) {

      gtk_container_remove(GTK_CONTAINER(game->container), game->buttons[i].selected);
      game->buttons[i].is_selected = 0;

      // Check if any dots on this track are selectable
      for (int j=0; j<game->num_dots; j++) {
        if (game->dots[j].track == i) {
          // If in boundary to press
          int total_distance = (game->max_height-BUTTONS_YOFFSET);
          if (game->dots[j].y >= total_distance - BUTTON_BOUNDARY && game->dots[j].y <= total_distance + BUTTON_BOUNDARY && !game->dots[j].pressed) {
            within_range = 1;
            game->dots[j].pressed = 1;
            // Play the sound
            char *sound_file = malloc(sizeof(char)*12);

            if (sound_file == NULL) {
              perror("sound_file malloc in events");
              exit(EXIT_FAILURE);
            }

            sprintf(sound_file, "wav/%c1.wav", game->dots[j].note);
            play_sound(sound_file, -1);
            game->score+=1;
            gtk_container_remove(GTK_CONTAINER(game->container), game->score_box);
            game->dots[j].removed = 1;
            gtk_container_remove(GTK_CONTAINER(game->container), game->dots[j].widget);
            draw_score(game);
          }
        }
      }

      if (!within_range) {
        // Play error sound
        char *sound_file = malloc(sizeof(char)*12);

        if (sound_file == NULL) {
          perror("sound_file malloc in events");
          exit(EXIT_FAILURE);
        }

        sprintf(sound_file, "wav/error.wav");
        play_sound(sound_file, -1);
        // Deduct score if score > 0;
        if (game->score > 0) {
          game->score-=1;
          gtk_container_remove(GTK_CONTAINER(game->container), game->score_box);
          draw_score(game);
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

  if (!game->dots[track].removed) {
    game->dots[track].y++;
    gtk_fixed_move(GTK_FIXED(game->container), game->dots[track].widget, game->dots[track].x, game->dots[track].y);
    if (game->dots[track].y > game->max_height) {
      game->dots[track].removed = 1;
      gtk_container_remove(GTK_CONTAINER(game->container), game->dots[track].widget);
      if (game->score > 0) {
        game->score-=1;
        gtk_container_remove(GTK_CONTAINER(game->container), game->score_box);
        draw_score(game);
      }
    }
  }

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
