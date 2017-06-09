#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>

#define ENTER_KEY 65293
#define Q_KEY 113
#define W_KEY 119
#define E_KEY 101
#define R_KEY 114
#define T_KEY 116

#define RED_KEY Q_KEY
#define BLUE_KEY W_KEY
#define GREEN_KEY E_KEY
#define YELLOW_KEY R_KEY
#define PURPLE_KEY T_KEY

GdkPixbuf *create_pixbuf(const gchar* filename);
void exit_button(GtkWidget* container);
void add_text(GtkWidget* container);

void start_game(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
void key_colour(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
void reset_colour(GtkWidget* window, GdkEventKey* event, gpointer user_data);

gboolean move_title(gpointer data);
