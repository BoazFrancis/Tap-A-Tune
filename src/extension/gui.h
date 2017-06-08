#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>

#define ENTER_KEY 65293

typedef struct {
  gpointer field_one;
  gpointer field_two;
} CallbackParams;

GdkPixbuf *create_pixbuf(const gchar * filename);
void set_favicon(GtkWidget* window);

void exit_button(GtkWidget* container);
void add_text(GtkWidget* container);

void key_event(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
