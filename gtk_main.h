#ifndef _INCLUDE_GTK_MAIN_H
#define _INCLUDE_GTK_MAIN_H

#ifndef S_SPLINT_S
/* Gtk headers return splint errors */
#include <gtk/gtk.h>

extern GtkWidget* fileselector_window;
extern GtkWidget* fileselector_cd_path;
extern GtkWidget* fileselector_cd_system;
extern GtkWidget* fileselector_rom_path;

extern GtkWidget* input_settings_window;
extern GtkWidget* general_settings_window;
extern GtkWidget* main_window;
extern GtkWidget* about_window;
extern GtkWidget* manual_window;

#endif


void set_gui_configuration_index(int new_index);
void build_gtk_interface (int argc, char* argv[]);
int get_gui_configuration_index();

#endif
