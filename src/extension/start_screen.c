#include "extension.h"

void set_bg(GtkWidget* window) {

  // Initialise bg pixmap
  GdkPixmap* bg;

  // Load bg image file into pixbuf
  GdkPixbuf* image = create_pixbuf(IMG_BG);

  // Image should fill screen size
  image = gdk_pixbuf_scale_simple(image, gdk_screen_width(), gdk_screen_height(), GDK_INTERP_BILINEAR);
  gdk_pixbuf_render_pixmap_and_mask(image, &bg, NULL, 0);

  // Create a new style
  GtkStyle* style = gtk_style_new();
  style->bg_pixmap[0] = bg;

  // Append the style to the window
  gtk_widget_set_style(GTK_WIDGET(window), GTK_STYLE(style));

}

void start_screen_text(GtkWidget* container) {

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

  GtkWidget* align_title = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(align_title), title);

  gtk_fixed_put(GTK_FIXED(container), align_title, 300, 300);
  gtk_fixed_put(GTK_FIXED(container), sub, 300, 400);

}

GdkPixbuf *create_pixbuf(const gchar* filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

void exit_button(GtkWidget* container) {

  GtkWidget* event_box = gtk_event_box_new();

  GdkColor bg;
  gdk_color_parse("black", &bg);
  gtk_widget_modify_bg(event_box, GTK_STATE_NORMAL, &bg);

  GdkPixbuf* icon = create_pixbuf(IMG_EXIT);
  GtkWidget* exit_image = gtk_image_new_from_pixbuf(icon);
  gtk_container_add(GTK_CONTAINER(event_box), exit_image);

  g_signal_connect(G_OBJECT(event_box), "button_press_event",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_fixed_put(GTK_FIXED(container), event_box, gdk_screen_width() - 128, 0);
  gtk_widget_set_size_request(event_box, 128, 128);

}
