#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>

GdkPixbuf *create_pixbuf(const gchar * filename);
void set_favicon(GtkWidget* window);

void exit_button(GtkWidget* container);
void show_dialog(GtkWidget *widget, gpointer window);
void add_text(GtkWidget* container);
