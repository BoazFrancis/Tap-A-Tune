#include "gui.h"

void create_button(GtkWidget* container) {

  // Create a new button
  GtkWidget* button = gtk_button_new_with_mnemonic("_Click here for cool stuff");
  gtk_fixed_put(GTK_FIXED(container), button, 150, 50);
  gtk_widget_set_size_request(button, 80, 30);

  // On click, call print_msg
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(show_dialog), NULL);

  // Mouse enters the button
  g_signal_connect(G_OBJECT(button), "enter", G_CALLBACK(enter_button), NULL);

  // Set a hover tooltip
  gtk_widget_set_tooltip_text(button, "Button widget");

}

void enter_button(GtkWidget *widget, gpointer data) {
  GdkColor col = {0, 27000, 30000, 35000};
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
}
