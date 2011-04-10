#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_main-server.h"
#include "callbacks-server.h"
#include "interface-server.h"
#include "support.h"
#include "hugod.h"

static  global_option_type global_option;	//!< Application global options

/*
  global_option.server_port = DEFAULT_SERVER_PORT;
  global_option.number_player = MAX_NUMBER_PLAYER;
  global_option.type_server = LAN_PROTOCOL_TYPE;
*/

void
on_button_launch_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkSpinButton* spin_button_players = NULL;
  GtkSpinButton* spin_button_port = NULL;
  GtkRadioButton* radio_button_mode = NULL;
  GtkButton* button_launch = NULL;
  GtkButton* button_stop = NULL;

  spin_button_players = (GtkSpinButton*)lookup_widget(window_main, "spinbutton_players");
  global_option.number_player = gtk_spin_button_get_value_as_int(spin_button_players);

  spin_button_port = (GtkSpinButton*)lookup_widget(window_main, "spinbutton_port");
  global_option.server_port = gtk_spin_button_get_value_as_int(spin_button_port);

  radio_button_mode = (GtkRadioButton*)lookup_widget(window_main, "radiobutton_lan");
  global_option.type_server = gtk_toggle_button_get_active((GtkToggleButton*)radio_button_mode) == TRUE ? LAN_PROTOCOL_TYPE : INTERNET_PROTOCOL_TYPE;

  button_launch = (GtkButton*)lookup_widget(window_main, "button_launch");
  gtk_widget_hide((GtkWidget*)button_launch);

  button_stop = (GtkButton*)lookup_widget(window_main, "button_stop");
  gtk_widget_show((GtkWidget*)button_stop);

  serve_dispatch (&global_option);  

}


void
on_button_help_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_show(window_help);
}

void
on_button_close_help_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(window_help);
}


gboolean
on_window_help_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gtk_widget_hide(window_help);
  return TRUE;
}


void
on_button_stop_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkButton* button_launch = NULL;
  GtkButton* button_stop = NULL;

  button_launch = (GtkButton*)lookup_widget(window_main, "button_launch");
  gtk_widget_show((GtkWidget*)button_launch);

  button_stop = (GtkButton*)lookup_widget(window_main, "button_stop");
  gtk_widget_hide((GtkWidget*)button_stop);
  
  gtk_stop_asked = TRUE;
}

