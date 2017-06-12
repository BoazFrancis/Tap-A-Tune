#include "extension.h"

void draw_buttons(GtkWidget* window, GdkEventKey* event, gpointer user_data) {
  if (event->keyval == ENTER_KEY) {

    GObject* params = user_data;
    GtkWidget** container = g_object_get_data(params, "container");
    GtkWidget* content = g_object_get_data(params, "content");

    gtk_container_remove(GTK_CONTAINER(*container), content);

    GtkWidget* red_button;
    GtkWidget* blue_button;
    GtkWidget* green_button;
    GtkWidget* yellow_button;
    GtkWidget* purple_button;
    GObject* new_params = g_object_new(G_TYPE_OBJECT, NULL);
    g_object_set_data(new_params, "red_button", red_button);
    g_object_set_data(new_params, "blue_button", blue_button);
    g_object_set_data(new_params, "green_button", green_button);
    g_object_set_data(new_params, "yellow_button", yellow_button);
    g_object_set_data(new_params, "purple_button", purple_button);
    g_object_set_data(new_params, "container", container);

    // Draw lines
    draw_lines(window, *container);
    draw_dot(*container);

    reset_colour(window, NULL, new_params);
    gtk_widget_show_all(window);

    // Don't care about this key press event anymore
    g_signal_handlers_disconnect_by_func(window, G_CALLBACK(draw_buttons), user_data);

    // Key presses for 5 different buttons
    g_signal_connect(window, "key-press-event", G_CALLBACK(key_colour), new_params);
    g_signal_connect(window, "key-release-event", G_CALLBACK(reset_colour), new_params);

  }
}

void draw_lines(GtkWidget* window, GtkWidget* container) {
  GdkPixbuf* line = create_pixbuf("img/line.png");
  GtkWidget* line_widget1 = gtk_image_new_from_pixbuf(line);
  GtkWidget* line_widget2 = gtk_image_new_from_pixbuf(line);
  GtkWidget* line_widget3 = gtk_image_new_from_pixbuf(line);
  GtkWidget* line_widget4 = gtk_image_new_from_pixbuf(line);
  GtkWidget* line_widget5 = gtk_image_new_from_pixbuf(line);
  gtk_fixed_put(GTK_FIXED(container), line_widget1, RED_X + BUTTONS_SIZE/2 - LINE_SIZE/2, 0);
  gtk_fixed_put(GTK_FIXED(container), line_widget2, BLUE_X + BUTTONS_SIZE/2 - LINE_SIZE/2, 0);
  gtk_fixed_put(GTK_FIXED(container), line_widget3, GREEN_X + BUTTONS_SIZE/2 - LINE_SIZE/2, 0);
  gtk_fixed_put(GTK_FIXED(container), line_widget4, YELLOW_X + BUTTONS_SIZE/2 - LINE_SIZE/2, 0);
  gtk_fixed_put(GTK_FIXED(container), line_widget5, PURPLE_X + BUTTONS_SIZE/2 - LINE_SIZE/2, 0);
}

void draw_dot(GtkWidget* container) {
  GtkWidget* align = gtk_alignment_new(0, 0, 0, 0);
  GdkPixbuf* dot = create_pixbuf("img/dot.png");
  GtkWidget* dot_widget = gtk_image_new_from_pixbuf(dot);
  gtk_container_add(GTK_CONTAINER(align), dot_widget);
  gtk_fixed_put(GTK_FIXED(container), align, RED_X, 0);
  g_timeout_add(10, move_title, align);
}

void reset_colour(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  GObject* params = user_data;

  GdkPixbuf* red_image = create_pixbuf(IMG_RED);
  red_image = gdk_pixbuf_scale_simple(red_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
  GtkWidget* red_button = g_object_get_data(params, "red_button");
  red_button = gtk_image_new_from_pixbuf(red_image);

  GdkPixbuf* blue_image = create_pixbuf(IMG_BLUE);
  blue_image = gdk_pixbuf_scale_simple(blue_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
  GtkWidget* blue_button = g_object_get_data(params, "blue_button");
  blue_button = gtk_image_new_from_pixbuf(blue_image);

  GdkPixbuf* green_image = create_pixbuf(IMG_GREEN);
  green_image = gdk_pixbuf_scale_simple(green_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
  GtkWidget* green_button = g_object_get_data(params, "green_button");
  green_button = gtk_image_new_from_pixbuf(green_image);

  GdkPixbuf* yellow_image = create_pixbuf(IMG_YELLOW);
  yellow_image = gdk_pixbuf_scale_simple(yellow_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
  GtkWidget* yellow_button = g_object_get_data(params, "yellow_button");
  yellow_button = gtk_image_new_from_pixbuf(yellow_image);

  GdkPixbuf* purple_image = create_pixbuf(IMG_PURPLE);
  purple_image = gdk_pixbuf_scale_simple(purple_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
  GtkWidget* purple_button = g_object_get_data(params, "purple_button");
  purple_button = gtk_image_new_from_pixbuf(purple_image);

  GtkWidget** container = g_object_get_data(params, "container");
  gtk_fixed_put(GTK_FIXED(*container), red_button, RED_X, BUTTONS_Y);
  gtk_fixed_put(GTK_FIXED(*container), blue_button, BLUE_X, BUTTONS_Y);
  gtk_fixed_put(GTK_FIXED(*container), green_button, GREEN_X, BUTTONS_Y);
  gtk_fixed_put(GTK_FIXED(*container), yellow_button, YELLOW_X, BUTTONS_Y);
  gtk_fixed_put(GTK_FIXED(*container), purple_button, PURPLE_X, BUTTONS_Y);
  gtk_widget_show_all(window);

}

void key_colour(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  GObject* params = user_data;
  GtkWidget** container = g_object_get_data(params, "container");

  switch (event->keyval) {

    case RED_KEY: {
      GtkWidget* red_button = g_object_get_data(params, "red_button");
      GdkPixbuf* red_image = create_pixbuf(IMG_RED_SELECT);
      red_image = gdk_pixbuf_scale_simple(red_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      red_button = gtk_image_new_from_pixbuf(red_image);
      gtk_fixed_put(GTK_FIXED(*container), red_button, RED_X, BUTTONS_Y);
      play_sound("wavs/piano/a1.wav", 600);
      break;
    }
    case BLUE_KEY: {
      GtkWidget* blue_button = g_object_get_data(params, "blue_button");
      GdkPixbuf* blue_image = create_pixbuf(IMG_BLUE_SELECT);
      blue_image = gdk_pixbuf_scale_simple(blue_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      blue_button = gtk_image_new_from_pixbuf(blue_image);
      gtk_fixed_put(GTK_FIXED(*container), blue_button, BLUE_X, BUTTONS_Y);
      play_sound("wavs/piano/b1.wav", 600);
      break;
    }
    case GREEN_KEY: {
      GtkWidget* green_button = g_object_get_data(params, "green_button");
      GdkPixbuf* green_image = create_pixbuf(IMG_GREEN_SELECT);
      green_image = gdk_pixbuf_scale_simple(green_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      green_button = gtk_image_new_from_pixbuf(green_image);
      gtk_fixed_put(GTK_FIXED(*container), green_button, GREEN_X, BUTTONS_Y);
      break;
    }
    case YELLOW_KEY: {
      GtkWidget* yellow_button = g_object_get_data(params, "yellow_button");
      GdkPixbuf* yellow_image = create_pixbuf(IMG_YELLOW_SELECT);
      yellow_image = gdk_pixbuf_scale_simple(yellow_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      yellow_button = gtk_image_new_from_pixbuf(yellow_image);
      gtk_fixed_put(GTK_FIXED(*container), yellow_button, YELLOW_X, BUTTONS_Y);
      break;
    }
    case PURPLE_KEY: {
      GtkWidget* purple_button = g_object_get_data(params, "purple_button");
      GdkPixbuf* purple_image = create_pixbuf(IMG_PURPLE_SELECT);
      purple_image = gdk_pixbuf_scale_simple(purple_image, BUTTONS_SIZE, BUTTONS_SIZE, GDK_INTERP_BILINEAR);
      purple_button = gtk_image_new_from_pixbuf(purple_image);
      gtk_fixed_put(GTK_FIXED(*container), purple_button, PURPLE_X, BUTTONS_Y);
      break;
    }
  }

  gtk_widget_show_all(window);

}
