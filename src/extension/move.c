#include "extension.h"

gboolean move_title(gpointer data) {

  int pad;
  gtk_alignment_get_padding(GTK_ALIGNMENT(data), &pad, NULL, NULL, NULL);
  gtk_alignment_set_padding(GTK_ALIGNMENT(data), pad + 1, 0, 0, 0);
  gtk_widget_queue_draw(data);

  if (pad > BUTTONS_Y) {
    return FALSE;
  }

  return TRUE;

}
