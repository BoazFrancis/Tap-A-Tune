#include "gui.h"

int main(int argc, char *argv[]) {

  // Initialise a Gtk window
  GtkWidget* window;
  gtk_init(&argc, &argv);

  // Set the window to TOPLEVEL i.e. has a border and title bar
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Set properties of the window
  gtk_window_set_title(GTK_WINDOW(window), "Our Extension");
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  set_favicon(window);

  gtk_widget_show(window);

  // When the user closes the window, exit the program
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Start the main loop
  gtk_main();

  return 0;

}