#include <gtk/gtk.h>


void
on_button_launch_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_help_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_close_help_clicked           (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_window_help_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_stop_clicked                 (GtkButton       *button,
                                        gpointer         user_data);
