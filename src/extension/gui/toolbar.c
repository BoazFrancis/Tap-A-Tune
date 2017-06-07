#include "gui.h"

void add_toolbar(GtkWidget* container) {

  GtkWidget* toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  GtkToolItem* newTb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);

  GtkToolItem* openTb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);

  GtkToolItem* saveTb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);

  GtkToolItem* sep = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

  GtkToolItem* exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

  gtk_fixed_put(GTK_FIXED(container), toolbar, 0, 0);
  gtk_widget_set_size_request(toolbar, 500, 40);

  g_signal_connect(G_OBJECT(exitTb), "clicked",
        G_CALLBACK(gtk_main_quit), NULL);

}
