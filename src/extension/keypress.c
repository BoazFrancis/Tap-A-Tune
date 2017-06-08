#include "gui.h"

void key_event(GtkWidget *widget, GdkEventKey *event) {
  if (event->keyval == 65293) {
    // <ENTER> key
    g_print("Pressed enter");
  }
}
