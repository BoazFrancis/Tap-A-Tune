#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>

GdkPixbuf *create_pixbuf(const gchar * filename);
void set_favicon(GtkWidget* window);

void create_button(GtkWidget* container);
void enter_button(GtkWidget *widget, gpointer data);

void add_toolbar(GtkWidget* container);

void show_dialog(GtkWidget *widget, gpointer window);
