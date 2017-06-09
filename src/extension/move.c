/*g_timeout_add(10, move_title, align_title);
gboolean move_title(gpointer data) {
int pad;
gtk_alignment_get_padding(GTK_ALIGNMENT(data), &pad, NULL, NULL, NULL);
gtk_alignment_set_padding(GTK_ALIGNMENT(data), pad + 10, 0, 0, 0);
gtk_widget_queue_draw(data);
if (pad > 600) {
  return FALSE;
}
return TRUE;
}
*/
