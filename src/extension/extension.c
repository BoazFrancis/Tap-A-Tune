#include "extension.h"

int main(int argc, char* argv[]) {

  // Initialise Gtk
  gtk_init(&argc, &argv);

  // Create a window to TOPLEVEL i.e. has a border and title bar
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Set properties of the window
  gtk_window_set_title(GTK_WINDOW(window), "Extension");
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_SIZE, WINDOW_SIZE);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_fullscreen(GTK_WINDOW(window));
  gtk_window_set_icon_from_file(GTK_WINDOW(window), IMG_ICON, NULL);

  set_bg(window);

  // Every visible object on the screen
  GtkWidget* container = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), container);
  exit_button(container);

  GObject* params = g_object_new(G_TYPE_OBJECT, NULL);
  GtkWidget* start_content = gtk_fixed_new();

  gtk_container_add(GTK_CONTAINER(container), start_content);
  start_screen_text(start_content);

  gtk_widget_show_all(window);

  // Press <ENTER> to start the game
  g_object_set_data(params, "container", &container);
  g_object_set_data(params, "content", start_content);
  g_signal_connect(window, "key-release-event", G_CALLBACK(draw_buttons), params);

  // When the user closes the window, exit the program
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Start the main loop
  gtk_main();

  return 0;

}
