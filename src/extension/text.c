#include "gui.h"

void add_text(GtkWidget* container) {

  PangoFontDescription* font_desc;
  GdkColor color;

  GtkWidget* title = gtk_label_new("Welcome to Tap Tap!");
  GtkWidget* sub = gtk_label_new("Press <ENTER> to start.");

  /* Change default font throughout the widget */
  font_desc = pango_font_description_from_string("Serif 40");
  gtk_widget_modify_font(title, font_desc);
  pango_font_description_free(font_desc);

  font_desc = pango_font_description_from_string("Serif 25");
  gtk_widget_modify_font(sub, font_desc);
  pango_font_description_free(font_desc);

  /* Change default color throughout the widget */
  gdk_color_parse("white", &color);
  gtk_widget_modify_fg(title, GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(sub, GTK_STATE_NORMAL, &color);

  gtk_fixed_put(GTK_FIXED(container), title, 300, 300);
  gtk_fixed_put(GTK_FIXED(container), sub, 300, 400);

}
