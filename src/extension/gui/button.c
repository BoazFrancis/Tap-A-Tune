#include "gui.h"

void create_button(GtkWidget* window) {

  GtkWidget* button;
  GtkWidget* halign;

  button = gtk_button_new_with_mnemonic("_Click here for cool stuff");

  g_signal_connect(button, "clicked", G_CALLBACK(print_msg), NULL);

  gtk_widget_set_tooltip_text(button, "Button widget");

  halign = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(halign), button);
  gtk_container_add(GTK_CONTAINER(window), halign);

}

void print_msg(GtkWidget *widget, gpointer window) {
  g_printf("Button clicked\n");
}
