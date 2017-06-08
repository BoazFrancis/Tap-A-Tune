#include "gui.h"

void key_event(GtkWidget* window, GdkEventKey* event, gpointer user_data) {
  if (event->keyval == ENTER_KEY) {
    CallbackParams* data = user_data;
    GtkWidget** container = data->field_one;

    gtk_container_remove(GTK_CONTAINER(*container), data->field_two);

    GdkPixbuf* red_image = create_pixbuf("red.png");
    red_image = gdk_pixbuf_scale_simple(red_image, 100, 100, GDK_INTERP_BILINEAR);
    GtkWidget* red_button = gtk_image_new_from_pixbuf(red_image);

    GdkPixbuf* blue_image = create_pixbuf("blue.png");
    blue_image = gdk_pixbuf_scale_simple(blue_image, 100, 100, GDK_INTERP_BILINEAR);
    GtkWidget* blue_button = gtk_image_new_from_pixbuf(blue_image);

    GdkPixbuf* green_image = create_pixbuf("green.png");
    green_image = gdk_pixbuf_scale_simple(green_image, 100, 100, GDK_INTERP_BILINEAR);
    GtkWidget* green_button = gtk_image_new_from_pixbuf(green_image);

    GdkPixbuf* yellow_image = create_pixbuf("yellow.png");
    yellow_image = gdk_pixbuf_scale_simple(yellow_image, 100, 100, GDK_INTERP_BILINEAR);
    GtkWidget* yellow_button = gtk_image_new_from_pixbuf(yellow_image);

    GdkPixbuf* purple_image = create_pixbuf("purple.png");
    purple_image = gdk_pixbuf_scale_simple(purple_image, 100, 100, GDK_INTERP_BILINEAR);
    GtkWidget* purple_button = gtk_image_new_from_pixbuf(purple_image);

    gtk_fixed_put(GTK_FIXED(*container), red_button, 0, 0);
    gtk_fixed_put(GTK_FIXED(*container), blue_button, 100, 0);
    gtk_fixed_put(GTK_FIXED(*container), green_button, 200, 0);
    gtk_fixed_put(GTK_FIXED(*container), yellow_button, 300, 0);
    gtk_fixed_put(GTK_FIXED(*container), purple_button, 400, 0);

    gtk_widget_show_all(window);

  }
}
