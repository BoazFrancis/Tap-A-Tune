#include "gui.h"

void add_text(GtkWidget* container) {

  GtkWidget* text;
  PangoFontDescription* font_desc;
  GdkColor color;

  text = gtk_label_new("Welcome to Tap Tap!");

  /* Change default font throughout the widget */
  font_desc = pango_font_description_from_string ("Serif 40");
  gtk_widget_modify_font (text, font_desc);
  pango_font_description_free (font_desc);

  /* Change default color throughout the widget */
  gdk_color_parse("white", &color);
  gtk_widget_modify_fg(text, GTK_STATE_NORMAL, &color);

  gtk_fixed_put(GTK_FIXED(container), text, 300, 300);

}
