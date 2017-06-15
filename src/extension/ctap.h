// Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

#define RED_LABEL "red"
#define GREEN_LABEL "green"
#define BLUE_LABEL "blue"
#define YELLOW_LABEL "yellow"
#define PURPLE_LABEL "purple"

#define WINDOW_SIZE 500
#define NUM_NOTES 7

// Images
#define IMG_PATH "img/"
#define IMG_BG IMG_PATH "bg.jpg"
#define IMG_ICON IMG_PATH "icon.png"
#define IMG_EXIT IMG_PATH "exit.png"

typedef struct {
  char *key;
  GtkWidget *widget;
  GtkWidget *selected;
  int is_selected;
} ctap_button_t;

typedef struct {
  GtkWidget *widget;
  int track;
  int x;
  int y;
  char note;
  int pressed;
} ctap_dot_t;

typedef struct {
  GtkWidget *window;
  GtkWidget *container;
  GtkWidget *content;
  GtkWidget *score_box;
  ctap_button_t *buttons;
  int num_buttons;
  ctap_dot_t *dots;
  int num_dots;
  int speed;
  int tempo;
  int *map;
  int max_height;
  int score;
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
GdkPixbuf *create_pixbuf(const gchar *filename);
char *trim_whitespace(char *str);
char *str_lower(char *str);

// Init methods
void init_window(ctap_t *game);
void init_container(ctap_t *game);
void init_startscreen(ctap_t *game);
void init_buttons(ctap_t *game);
void set_bg(ctap_t *game);
void start_screen_text(ctap_t *game);
void exit_button(ctap_t *game);
void init_notetable(ctap_t *game);
void init_score(ctap_t *game);


// Draw methods
void draw_buttons(ctap_t *game);
void draw_dot(ctap_t *game, char note);
void draw_lines(ctap_t *game);
void draw_score(ctap_t *game);

// Event callbacks
void start_game(GtkWidget*widget, GdkEventKey *event, gpointer user_data);
void select_button(GtkWidget*widget, GdkEventKey *event, gpointer user_data);
void release_button(GtkWidget *window, GdkEventKey *event, gpointer user_data);
gboolean move_dot(gpointer user_data);
gboolean create_note(gpointer user_data);

// Sounds
void play_sound(char *wav_file_name, int length);

// Reading in a file
char **read_file(char *filepath);
int count_lines(char *filepath);

// Start song
void start_song(ctap_t *game);
