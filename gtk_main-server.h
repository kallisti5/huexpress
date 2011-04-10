#ifndef _INCLUDE_GTK_MAIN_SERVER_H
#define _INCLUDE_GTK_MAIN_SERVER_H

#ifndef S_SPLINT_S
/* Gtk headers return splint errors */
#include <gtk/gtk.h>

extern GtkWidget* window_main;
extern GtkWidget* window_help;
extern gboolean gtk_stop_asked;

#endif

void build_gtk_interface (int argc, char* argv[]);

#endif
