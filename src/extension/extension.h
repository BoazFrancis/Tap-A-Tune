// Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include "SDL.h"
#include "SDL_mixer.h"

// Constants
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

#define WINDOW_SIZE 500

// Images
#define IMG_PATH "img/"
#define IMG_BG IMG_PATH "bg.jpg"
#define IMG_ICON IMG_PATH "icon.png"
#define IMG_RED IMG_PATH "red.png"
#define IMG_RED_SELECT IMG_PATH "red_selected.png"
#define IMG_BLUE IMG_PATH "blue.png"
#define IMG_BLUE_SELECT IMG_PATH "blue_selected.png"
#define IMG_GREEN IMG_PATH "green.png"
#define IMG_GREEN_SELECT IMG_PATH "green_selected.png"
#define IMG_YELLOW IMG_PATH "yellow.png"
#define IMG_YELLOW_SELECT IMG_PATH "yellow_selected.png"
#define IMG_PURPLE IMG_PATH "purple.png"
#define IMG_PURPLE_SELECT IMG_PATH "purple_selected.png"
#define IMG_EXIT IMG_PATH "exit.png"

#define BUTTONS_Y gdk_screen_height()-200
#define RED_X 50
#define BLUE_X 200
#define GREEN_X 350
#define YELLOW_X 500
#define PURPLE_X 650
#define BUTTONS_SIZE 100
#define LINE_SIZE 10

// Start screen methods
void set_bg(GtkWidget* window);
void start_screen(GtkWidget* window, GtkWidget* container, GObject* params, GtkWidget* start_content);
GdkPixbuf *create_pixbuf(const gchar* filename);
void exit_button(GtkWidget* container);
void start_screen_text(GtkWidget* container);

// Initialise buttons
void draw_dot(GtkWidget* container);
void draw_lines(GtkWidget* window, GtkWidget* container);
void draw_buttons(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
void key_colour(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
void reset_colour(GtkWidget* window, GdkEventKey* event, gpointer user_data);

// Move
gboolean move_title(gpointer data);

// Sounds
void play_sound(char* wav_file_name, int time);

// Reading in a file
char** readfile();
