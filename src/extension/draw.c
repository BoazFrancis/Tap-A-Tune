#include "ctap.h"

void draw_buttons(ctap_t *game) {

  for (int i=0; i<game->num_buttons; i++) {
    gtk_fixed_put(GTK_FIXED(game->container), game->buttons[i].widget,
            BUTTONS_XOFFSET + i*BUTTONS_XINC, game->max_height-BUTTONS_YOFFSET);
  }

  gtk_widget_show_all(game->window);

}

void draw_lines(ctap_t *game) {

  char filename[100];
  sprintf(filename, "%s/../src/extension/img/line.png", game->path);
  GdkPixbuf *line = create_pixbuf(filename);
  int posX = BUTTONS_XOFFSET + BUTTONS_SIZE/2 - LINE_SIZE/2;

  for (int i=0; i<game->num_buttons; i++) {
    GtkWidget *line_widget = gtk_image_new_from_pixbuf(line);
    gtk_fixed_put(GTK_FIXED(game->container), line_widget, posX + i*BUTTONS_XINC, 0);
  }

}

void draw_dot(ctap_t *game, char note) {

  int index = note - 'a';
  int track = game->map[index];

  GtkWidget *align = gtk_alignment_new(0, 0, 0, 0);
  char filename[100];
  sprintf(filename, "%s/../src/extension/img/dot.png", game->path);
  GdkPixbuf *dot = create_pixbuf(filename);
  GtkWidget *dot_widget = gtk_image_new_from_pixbuf(dot);
  gtk_container_add(GTK_CONTAINER(align), dot_widget);

  game->num_dots++;
  game->dots = realloc(game->dots, sizeof(ctap_dot_t) * game->num_dots);
  if (game->dots == NULL) {
    perror("game->dots realloc in draw");
    exit(EXIT_FAILURE);
  }

  game->dots[game->num_dots - 1].widget = align;
  game->dots[game->num_dots - 1].track = track;
  game->dots[game->num_dots - 1].x = BUTTONS_XOFFSET + track*BUTTONS_XINC;
  game->dots[game->num_dots - 1].y = 0;
  game->dots[game->num_dots - 1].note = note;
  game->dots[game->num_dots - 1].pressed = 0;
  game->dots[game->num_dots - 1].removed = 0;

  gtk_fixed_put(GTK_FIXED(game->container), game->dots[game->num_dots - 1].widget,
          game->dots[game->num_dots - 1].x, game->dots[game->num_dots - 1].y);

  for (int i=0; i<game->max_height+BUTTONS_SIZE; i++) {
    GObject *params = g_object_new(G_TYPE_OBJECT, NULL);
    g_object_set_data(params, "game", game);
    g_object_set_data(params, "track", GINT_TO_POINTER(game->num_dots - 1));
    int timeout = 10 - game->speed;
    g_timeout_add(timeout*i, move_dot, params);
  }

}

void draw_score(ctap_t *game) {

  game->score_box = gtk_label_new("");
  PangoFontDescription *font_desc;
  GdkColor color;

  gchar* buf = g_strdup_printf("Score: %i", game->score);
  gtk_label_set_text(GTK_LABEL(game->score_box), buf);

  // Change default font throughout the widget
  font_desc = pango_font_description_from_string("Serif 70");
  gtk_widget_modify_font(game->score_box, font_desc);
  pango_font_description_free(font_desc);

  gdk_color_parse("white", &color);
  gtk_widget_modify_fg(game->score_box, GTK_STATE_NORMAL, &color);

  gtk_fixed_put(GTK_FIXED(game->container), game->score_box,
          gdk_screen_width() - 1010, gdk_screen_height() - 300);
  gtk_widget_set_size_request(game->score_box, 1000, 200);

  gtk_widget_show_all(game->window);

}

void draw_escape(ctap_t *game) {

  PangoFontDescription *font_desc;
  GdkColor color;

  GtkWidget *escape = gtk_label_new("Press ESC button to exit game");

  // Change default font throughout the widget
  font_desc = pango_font_description_from_string("Serif 30");
  gtk_widget_modify_font(escape, font_desc);
  pango_font_description_free(font_desc);


  // Change default color throughout the widget
  gdk_color_parse("white", &color);
  gtk_widget_modify_fg(escape, GTK_STATE_NORMAL, &color);

  GtkWidget *align_escape = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(align_escape), escape);

  gtk_fixed_put(GTK_FIXED(game->container), align_escape,
          gdk_screen_width() - 700, gdk_screen_height() - 50);

}
