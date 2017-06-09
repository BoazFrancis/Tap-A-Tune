#include "gui.h"

int main(int argc, char* argv[]) {

  // Initialise Gtk
  gtk_init(&argc, &argv);

  // Create a window to TOPLEVEL i.e. has a border and title bar
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Set properties of the window
  gtk_window_set_title(GTK_WINDOW(window), "Tap Tap");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_fullscreen(GTK_WINDOW(window));
  gtk_window_set_icon_from_file(GTK_WINDOW(window), "img/icon.png", NULL);

  GdkPixmap* bg;
  GdkPixbuf* image = create_pixbuf("img/bg.jpg");

  image = gdk_pixbuf_scale_simple(image, gdk_screen_width(), gdk_screen_height(), GDK_INTERP_BILINEAR);
  gdk_pixbuf_render_pixmap_and_mask(image, &bg, NULL, 0);
  GtkStyle* style = gtk_style_new();
  style->bg_pixmap[0] = bg;
  gtk_widget_set_style(GTK_WIDGET(window), GTK_STYLE(style));

  // Every visible object on the screen
  GtkWidget* container = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), container);
  exit_button(container);

  // A container for all the on-screen content
  GtkWidget* start_content = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(container), start_content);
  add_text(start_content);

  gtk_widget_show_all(window);

  // Press <ENTER> to start the game
  GObject* params = g_object_new(G_TYPE_OBJECT, NULL);
  g_object_set_data(params, "container", &container);
  g_object_set_data(params, "content", start_content);
  g_signal_connect(window, "key-release-event", G_CALLBACK(start_game), params);

  // When the user closes the window, exit the program
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Start the main loop
  gtk_main();

  return 0;

}
