#include "gui.h"

void exit_button(GtkWidget* container) {

  GtkWidget* event_box = gtk_event_box_new();

  GdkColor bg;
  gdk_color_parse("black", &bg);
  gtk_widget_modify_bg(event_box, GTK_STATE_NORMAL, &bg);

  GdkPixbuf* icon = create_pixbuf("exit.png");
  GtkWidget* exit_image = gtk_image_new_from_pixbuf(icon);
  gtk_container_add (GTK_CONTAINER (event_box), exit_image);

  g_signal_connect(G_OBJECT(event_box), "button_press_event",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_fixed_put(GTK_FIXED(container), event_box, 0, 0);
  gtk_widget_set_size_request(event_box, 128, 128);

}
