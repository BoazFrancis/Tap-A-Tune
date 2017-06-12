#include "extension.h"

gboolean move_dot(gpointer data) {

  GObject* params = data;
  GtkWidget* window = g_object_get_data(data, "window");
  GtkWidget* align = g_object_get_data(data, "align");

  int pad;
  gtk_alignment_get_padding(GTK_ALIGNMENT(align), &pad, NULL, NULL, NULL);
  gtk_alignment_set_padding(GTK_ALIGNMENT(align), pad + 1, 0, 0, 0);
  gtk_widget_queue_draw(align);

  int height;
  gtk_window_get_size(GTK_WINDOW(window), NULL, &height);

  if (pad > height-BUTTONS_YOFFSET) {
    return FALSE;
  }

  return FALSE;

}
