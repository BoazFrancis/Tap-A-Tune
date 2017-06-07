#include "gui.h"

void create_button(GtkWidget* container) {

  // Create a new button
  GtkWidget* button = gtk_button_new_with_mnemonic("_Click here for cool stuff");
  gtk_fixed_put(GTK_FIXED(container), button, 150, 50);
  gtk_widget_set_size_request(button, 80, 30);

  // On click, call print_msg
  g_signal_connect(button, "clicked", G_CALLBACK(print_msg), NULL);

  // Set a hover tooltip
  gtk_widget_set_tooltip_text(button, "Button widget");

}

void print_msg(GtkWidget *widget, gpointer window) {
  g_printf("Button clicked\n");
}
