#include "gui.h"

GdkPixbuf *create_pixbuf(const gchar* filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

void set_favicon(GtkWidget* window) {

  GdkPixbuf* icon;
  icon = create_pixbuf("icon.png");

  // Set the image as the icon for the window
  gtk_window_set_icon(GTK_WINDOW(window), icon);

  // No longer need reference to the image anymore
  g_object_unref(icon);

}
