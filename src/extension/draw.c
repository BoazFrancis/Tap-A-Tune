#include "ctap.h"

void draw_buttons(ctap_t *game) {

  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  for (int i=0; i<game->num_buttons; i++) {
    gtk_fixed_put(GTK_FIXED(game->container), game->buttons[i].widget, BUTTONS_XOFFSET + i*BUTTONS_XINC, height-BUTTONS_YOFFSET);
  }

  gtk_widget_show_all(game->window);

}

void draw_lines(ctap_t *game) {

  GdkPixbuf *line = create_pixbuf("img/line.png");
  int posX = BUTTONS_XOFFSET + BUTTONS_SIZE/2 - LINE_SIZE/2;

  for (int i=0; i<game->num_buttons; i++) {
    GtkWidget *line_widget = gtk_image_new_from_pixbuf(line);
    gtk_fixed_put(GTK_FIXED(game->container), line_widget, posX + i*BUTTONS_XINC, 0);
  }

}

void draw_dot(ctap_t *game, int track) {

  GtkWidget *align = gtk_alignment_new(0, 0, 0, 0);
  GdkPixbuf *dot = create_pixbuf("img/dot.png");
  GtkWidget *dot_widget = gtk_image_new_from_pixbuf(dot);
  gtk_container_add(GTK_CONTAINER(align), dot_widget);

  game->num_dots++;
  game->dots = realloc(game->dots, sizeof(ctap_dot_t) * game->num_dots);
  game->dots[game->num_dots - 1].widget = align;
  game->dots[game->num_dots - 1].track = track;
  game->dots[game->num_dots - 1].x = BUTTONS_XOFFSET + track*BUTTONS_XINC;
  game->dots[game->num_dots - 1].y = 0;

  gtk_fixed_put(GTK_FIXED(game->container), game->dots[game->num_dots - 1].widget, game->dots[game->num_dots - 1].x, game->dots[game->num_dots - 1].y);

  int height;
  gtk_window_get_size(GTK_WINDOW(game->window), NULL, &height);
  for (int i=0; i<height+BUTTONS_SIZE; i++) {
    GObject *params = g_object_new(G_TYPE_OBJECT, NULL);
    g_object_set_data(params, "game", game);
    g_object_set_data(params, "track", GINT_TO_POINTER(game->num_dots - 1));
    g_timeout_add(5*i, move_dot, params);
  }

}
