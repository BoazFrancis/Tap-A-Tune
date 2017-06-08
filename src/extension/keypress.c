#include "gui.h"

void key_event(GtkWidget* window, GdkEventKey* event, gpointer user_data) {
  if (event->keyval == ENTER_KEY) {
    CallbackParams* data = user_data;
    gtk_container_remove(GTK_CONTAINER(data->field_one), data->field_two);
  }
}
