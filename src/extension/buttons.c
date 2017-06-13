#include "ctap.h"

void draw_lines(ctap_t *game) {
/*
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
*/
}

void draw_dot(ctap_t *game) {
/*
  GtkWidget* align = gtk_alignment_new(0, 0, 0, 0);
  GdkPixbuf* dot = create_pixbuf("img/dot.png");
  GtkWidget* dot_widget = gtk_image_new_from_pixbuf(dot);
  gtk_container_add(GTK_CONTAINER(align), dot_widget);
  gtk_fixed_put(GTK_FIXED(container), align, RED_X, 0);

  int height;
  gtk_window_get_size(GTK_WINDOW(window), NULL, &height);
  GObject* params = g_object_new(G_TYPE_OBJECT, NULL);
  g_object_set_data(params, "align", align);
  g_object_set_data(params, "window", window);
  for (int i=0; i<(height-BUTTONS_YOFFSET); i++) {
    g_timeout_add(5*i, move_dot, params);
  }
*/
}
