#include "ctap.h"

void start_game(GtkWidget* window, GdkEventKey* event, gpointer user_data) {
  if (event->keyval == ENTER_KEY) {

    ctap_t *game = user_data;

    gtk_container_remove(GTK_CONTAINER(game->container), game->content);

    // Draw lines
    draw_lines(game);
    draw_dot(game);

    draw_buttons(window, NULL, game);
    gtk_widget_show_all(game->window);

    // Don't care about this key press event anymore
    g_signal_handlers_disconnect_by_func(game->window, G_CALLBACK(start_game), user_data);

    // Key presses for 5 different buttons
    g_signal_connect(game->window, "key-press-event", G_CALLBACK(select_button), game);
    g_signal_connect(game->window, "key-release-event", G_CALLBACK(draw_buttons), game);

  }
}

void draw_buttons(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  ctap_t *game = user_data;

  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  for (int i=0; i<game->num_buttons; i++) {
    gtk_fixed_put(GTK_FIXED(game->container), game->buttons[i].widget, BUTTONS_XOFFSET + i*BUTTONS_XINC, height-BUTTONS_YOFFSET);
  }

  gtk_widget_show_all(game->window);

}

void select_button(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  /*GObject* params = user_data;
  GtkWidget** container = g_object_get_data(params, "container");
  int height;
  gtk_window_get_size(GTK_WINDOW(window), NULL, &height);

  switch (event->keyval) {
    case RED_KEY: {
      GtkWidget* red_button = g_object_get_data(params, "red_button");
      GdkPixbuf* red_image = create_pixbuf(IMG_RED_SELECT);
      red_image = gdk_pixbuf_scale_simple(red_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      red_button = gtk_image_new_from_pixbuf(red_image);
      gtk_fixed_put(GTK_FIXED(*container), red_button, RED_X, height-BUTTONS_YOFFSET);
      play_sound("wavs/piano/a1.wav", 600);
      break;
    }
    case BLUE_KEY: {
      GtkWidget* blue_button = g_object_get_data(params, "blue_button");
      GdkPixbuf* blue_image = create_pixbuf(IMG_BLUE_SELECT);
      blue_image = gdk_pixbuf_scale_simple(blue_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      blue_button = gtk_image_new_from_pixbuf(blue_image);
      gtk_fixed_put(GTK_FIXED(*container), blue_button, BLUE_X, height-BUTTONS_YOFFSET);
      play_sound("wavs/piano/b1.wav", 600);
      break;
    }
    case GREEN_KEY: {
      GtkWidget* green_button = g_object_get_data(params, "green_button");
      GdkPixbuf* green_image = create_pixbuf(IMG_GREEN_SELECT);
      green_image = gdk_pixbuf_scale_simple(green_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      green_button = gtk_image_new_from_pixbuf(green_image);
      gtk_fixed_put(GTK_FIXED(*container), green_button, GREEN_X, height-BUTTONS_YOFFSET);
      break;
    }
    case YELLOW_KEY: {
      GtkWidget* yellow_button = g_object_get_data(params, "yellow_button");
      GdkPixbuf* yellow_image = create_pixbuf(IMG_YELLOW_SELECT);
      yellow_image = gdk_pixbuf_scale_simple(yellow_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      yellow_button = gtk_image_new_from_pixbuf(yellow_image);
      gtk_fixed_put(GTK_FIXED(*container), yellow_button, YELLOW_X, height-BUTTONS_YOFFSET);
      break;
    }
    case PURPLE_KEY: {
      GtkWidget* purple_button = g_object_get_data(params, "purple_button");
      GdkPixbuf* purple_image = create_pixbuf(IMG_PURPLE_SELECT);
      purple_image = gdk_pixbuf_scale_simple(purple_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      purple_button = gtk_image_new_from_pixbuf(purple_image);
      gtk_fixed_put(GTK_FIXED(*container), purple_button, PURPLE_X, height-BUTTONS_YOFFSET);
      break;
    }
  }

  gtk_widget_show_all(window);*/

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
