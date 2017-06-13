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

typedef struct {
  char *key;
  GtkWidget *widget;
  GtkWidget *selected;
  int active;
} ctap_button_t;

typedef struct {
  GtkWidget *window;
  GtkWidget *container;
  GtkWidget *content;
  ctap_button_t *buttons;
  int num_buttons;
} ctap_t;

enum {
  BUTTONS_YOFFSET = 150,
  BUTTONS_XOFFSET = 50,
  BUTTONS_XINC    = 150,
  BUTTONS_SIZE    = 100,
  LINE_SIZE       = 10,
  BUTTON_BOUNDARY = 50
};

// Utils methodss
GdkPixbuf *create_pixbuf(const gchar* filename);

// Init methods
void init_window(ctap_t *game);
void init_container(ctap_t *game);
void init_startscreen(ctap_t *game);
void init_buttons(ctap_t *game);
void set_bg(ctap_t *game);
void start_screen_text(ctap_t *game);
void exit_button(ctap_t *game);

// Draw methods
void draw_dot(ctap_t *game);
void draw_lines(ctap_t *game);

// Event callbacks
void start_game(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
void select_button(GtkWidget*widget, GdkEventKey* event, gpointer user_data);
void draw_buttons(GtkWidget* window, GdkEventKey* event, gpointer user_data);
gboolean move_dot(gpointer data);

// Sounds
void play_sound(char* wav_file_name, int time);

// Reading in a file
char** read_file(char* filepath);