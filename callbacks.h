#include <gtk/gtk.h>


void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_load1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_input_setting_1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_hugo_manual1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_mainWindow_destroy                  (GtkObject       *object,
                                        gpointer         user_data);

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_button1_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_button1_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_option_config_number_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_close_input_settings_window_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_general_settings_1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button_close_about_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_browse_cd_system_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttongeneral_config_close_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_general_config_save_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_general_config_cancel_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_general_settings_window_show        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_ok_button_cd_system_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_button_cd_system_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_button_cd_path_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_button_cd_path_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_browse_rom_dirname_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_browse_cd_path_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_button_rom_path_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_button_rom_path_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_manual_close_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_input_settings_window_show          (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_open_cd1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_settings1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open_cd1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_settings1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_option_config_number_changed        (GtkOptionMenu   *optionmenu,
                                        gpointer         user_data);

void
on_button_input_configuration_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_input_configuration_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_spinbutton_configuration_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_window_input_settings_show          (GtkWidget       *widget,
                                        gpointer         user_data);

gboolean
on_window_input_settings_delete_event  (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_input_ok_activate            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_input_cancel_activate        (GtkButton       *button,
                                        gpointer         user_data);

void
on_spinbutton_joydev_value_changed     (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_general_settings_window_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_fileselection_cd_system_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_fileselection_cd_path_delete_event  (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_fileselection_rom_path_delete_event (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_fileselection1_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_window_about_delete_event           (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);
