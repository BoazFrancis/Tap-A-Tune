#include "ctap.h"

void start_game(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  if (event->keyval == ENTER_KEY) {

    ctap_t *game = user_data;

    gtk_container_remove(GTK_CONTAINER(game->container), game->content);

    // Draw lines
    draw_lines(game);
    draw_dot(game);

    draw_buttons(game);
    gtk_widget_show_all(game->window);

    // Don't care about this key press event anymore
    g_signal_handlers_disconnect_by_func(game->window, G_CALLBACK(start_game), user_data);

    // Key presses for 5 different buttons
    g_signal_connect(game->window, "key-press-event", G_CALLBACK(select_button), game);
    g_signal_connect(game->window, "key-release-event", G_CALLBACK(release_button), game);

  }
}

void select_button(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  ctap_t *game = user_data;
  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  char *label;

  switch (event->keyval) {
    case RED_KEY: label = RED_LABEL; break;
    case BLUE_KEY: label = BLUE_LABEL; break;
    case GREEN_KEY: label = GREEN_LABEL; break;
    case YELLOW_KEY: label = YELLOW_LABEL; break;
    case PURPLE_KEY: label = PURPLE_LABEL; break;
  }

  for (int i=0; i<game->num_buttons; i++) {
    if (strcmp(game->buttons[i].key, label) == 0 && game->buttons[i].active == 0) {
      gtk_fixed_put(GTK_FIXED(game->container), game->buttons[i].selected, BUTTONS_XOFFSET + i*BUTTONS_XINC, height-BUTTONS_YOFFSET);
      game->buttons[i].active = 1;
    }
  }

  gtk_widget_show_all(window);

}

void release_button(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  ctap_t *game = user_data;

  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  for (int i=0; i<game->num_buttons; i++) {
    if (game->buttons[i].active == 1) {
      gtk_container_remove(GTK_CONTAINER(game->container), game->buttons[i].selected);
      game->buttons[i].active = 0;
    }
  }

  gtk_widget_show_all(game->window);

}

gboolean move_dot(gpointer data) {

  /*GObject* params = data;
  GtkWidget* window = g_object_get_data(data, "window");
  GtkWidget* align = g_object_get_data(data, "align");

  int pad;
  gtk_alignment_get_padding(GTK_ALIGNMENT(align), &pad, NULL, NULL, NULL);
  gtk_alignment_set_padding(GTK_ALIGNMENT(align), pad + 1, 0, 0, 0);
  gtk_widget_queue_draw(align);

  int height;
  gtk_window_get_size(GTK_WINDOW(window), NULL, &height);

  // If in boundary to press
  int total_distance = (height-BUTTONS_YOFFSET);
  if (pad >= total_distance - 50 && pad <= total_distance + 50) {

  }

  return FALSE;*/

}
