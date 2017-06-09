#include "gui.h"
#include "sound.h"

void start_game(GtkWidget* window, GdkEventKey* event, gpointer user_data) {
  if (event->keyval == ENTER_KEY) {

    GObject* params = user_data;
    GtkWidget** container = g_object_get_data(params, "container");
    GtkWidget* content = g_object_get_data(params, "content");

    gtk_container_remove(GTK_CONTAINER(*container), content);

    GtkWidget* red_button = malloc(sizeof(GtkWidget*));
    GtkWidget* blue_button = malloc(sizeof(GtkWidget*));
    GtkWidget* green_button = malloc(sizeof(GtkWidget*));
    GtkWidget* yellow_button = malloc(sizeof(GtkWidget*));
    GtkWidget* purple_button = malloc(sizeof(GtkWidget*));
    GObject* new_params = g_object_new(G_TYPE_OBJECT, NULL);
    g_object_set_data(new_params, "red_button", red_button);
    g_object_set_data(new_params, "blue_button", blue_button);
    g_object_set_data(new_params, "green_button", green_button);
    g_object_set_data(new_params, "yellow_button", yellow_button);
    g_object_set_data(new_params, "purple_button", purple_button);
    g_object_set_data(new_params, "container", container);
    reset_colour(window, NULL, new_params);

    // Don't care about this key press event anymore
    g_signal_handlers_disconnect_by_func(window, G_CALLBACK(start_game), user_data);

    // Key presses for 5 different buttons
    g_signal_connect(window, "key-press-event", G_CALLBACK(key_colour), new_params);
    g_signal_connect(window, "key-release-event", G_CALLBACK(reset_colour), new_params);

  }
}

void reset_colour(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  GObject* params = user_data;

  GdkPixbuf* red_image = create_pixbuf("img/red.png");
  red_image = gdk_pixbuf_scale_simple(red_image, 100, 100, GDK_INTERP_BILINEAR);
  GtkWidget* red_button = g_object_get_data(params, "red_button");
  red_button = gtk_image_new_from_pixbuf(red_image);

  GdkPixbuf* blue_image = create_pixbuf("img/blue.png");
  blue_image = gdk_pixbuf_scale_simple(blue_image, 100, 100, GDK_INTERP_BILINEAR);
  GtkWidget* blue_button = g_object_get_data(params, "blue_button");
  blue_button = gtk_image_new_from_pixbuf(blue_image);

  GdkPixbuf* green_image = create_pixbuf("img/green.png");
  green_image = gdk_pixbuf_scale_simple(green_image, 100, 100, GDK_INTERP_BILINEAR);
  GtkWidget* green_button = g_object_get_data(params, "green_button");
  green_button = gtk_image_new_from_pixbuf(green_image);

  GdkPixbuf* yellow_image = create_pixbuf("img/yellow.png");
  yellow_image = gdk_pixbuf_scale_simple(yellow_image, 100, 100, GDK_INTERP_BILINEAR);
  GtkWidget* yellow_button = g_object_get_data(params, "yellow_button");
  yellow_button = gtk_image_new_from_pixbuf(yellow_image);

  GdkPixbuf* purple_image = create_pixbuf("img/purple.png");
  purple_image = gdk_pixbuf_scale_simple(purple_image, 100, 100, GDK_INTERP_BILINEAR);
  GtkWidget* purple_button = g_object_get_data(params, "purple_button");
  purple_button = gtk_image_new_from_pixbuf(purple_image);

  GtkWidget** container = g_object_get_data(params, "container");
  gtk_fixed_put(GTK_FIXED(*container), red_button, 0, 0);
  gtk_fixed_put(GTK_FIXED(*container), blue_button, 100, 0);
  gtk_fixed_put(GTK_FIXED(*container), green_button, 200, 0);
  gtk_fixed_put(GTK_FIXED(*container), yellow_button, 300, 0);
  gtk_fixed_put(GTK_FIXED(*container), purple_button, 400, 0);

  gtk_widget_show_all(window);

}

void key_colour(GtkWidget* window, GdkEventKey* event, gpointer user_data) {

  GObject* params = user_data;
  GtkWidget** container = g_object_get_data(params, "container");

  switch (event->keyval) {

    case RED_KEY: {
      GtkWidget* red_button = g_object_get_data(params, "red_button");
      GdkPixbuf* red_image = create_pixbuf("img/red_selected.png");
      red_image = gdk_pixbuf_scale_simple(red_image, 100, 100, GDK_INTERP_BILINEAR);
      red_button = gtk_image_new_from_pixbuf(red_image);
      gtk_fixed_put(GTK_FIXED(*container), red_button, 0, 0);
      play_sound("wavs/piano/a1.wav", 600);
      break;
    }
    case BLUE_KEY: {
      GtkWidget* blue_button = g_object_get_data(params, "blue_button");
      GdkPixbuf* blue_image = create_pixbuf("img/blue_selected.png");
      blue_image = gdk_pixbuf_scale_simple(blue_image, 100, 100, GDK_INTERP_BILINEAR);
      blue_button = gtk_image_new_from_pixbuf(blue_image);
      gtk_fixed_put(GTK_FIXED(*container), blue_button, 100, 0);
      play_sound("wavs/piano/b1.wav", 600);
      break;
    }
    case GREEN_KEY: {
      GtkWidget* green_button = g_object_get_data(params, "green_button");
      GdkPixbuf* green_image = create_pixbuf("img/green_selected.png");
      green_image = gdk_pixbuf_scale_simple(green_image, 100, 100, GDK_INTERP_BILINEAR);
      green_button = gtk_image_new_from_pixbuf(green_image);
      gtk_fixed_put(GTK_FIXED(*container), green_button, 200, 0);
      break;
    }
    case YELLOW_KEY: {
      GtkWidget* yellow_button = g_object_get_data(params, "yellow_button");
      GdkPixbuf* yellow_image = create_pixbuf("img/yellow_selected.png");
      yellow_image = gdk_pixbuf_scale_simple(yellow_image, 100, 100, GDK_INTERP_BILINEAR);
      yellow_button = gtk_image_new_from_pixbuf(yellow_image);
      gtk_fixed_put(GTK_FIXED(*container), yellow_button, 300, 0);
      break;
    }
    case PURPLE_KEY: {
      GtkWidget* purple_button = g_object_get_data(params, "purple_button");
      GdkPixbuf* purple_image = create_pixbuf("img/purple_selected.png");
      purple_image = gdk_pixbuf_scale_simple(purple_image, 100, 100, GDK_INTERP_BILINEAR);
      purple_button = gtk_image_new_from_pixbuf(purple_image);
      gtk_fixed_put(GTK_FIXED(*container), purple_button, 400, 0);
      break;
    }
  }

  gtk_widget_show_all(window);

}
