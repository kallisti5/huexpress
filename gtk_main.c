#include "gtk_main.h"
#include "interface.h"
#include "support.h"
#include "callbacks.h"
#include "sys_inp.h"
#include "iniconfig.h"


#if defined(SDL)
  #include "SDL.h"
#endif

#if defined(SDL_mixer)
  #include "SDL_mixer.h"
#endif

void gtk_show_config_device(int device_index);
void attach_input_signal(GtkWidget* input_window);
void gtk_update_configuration(gboolean);
void gtk_update_player_configuration(int player_index, individual_input_config individual_configuration, gboolean);

static char tmp_buf[100];

static input_config temporary_configuration[16];

GtkWidget* fileselector_window = NULL;
GtkWidget* fileselector_cd_path = NULL;
GtkWidget* fileselector_cd_system = NULL;
GtkWidget* fileselector_rom_path = NULL;

GtkWidget* input_settings_window = NULL;
GtkWidget* general_settings_window = NULL;
GtkWidget* main_window = NULL;
GtkWidget* about_window = NULL;
GtkWidget* manual_window = NULL;

int gtk_stop_asked = 0;

void gtk_show_config_player(int player_index);

#include "manual.h"

//! Construct the gtk interface
void build_gtk_interface (int argc, char* argv[])
{
  GtkTextView* manual_text = NULL;
	
  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (".");
  add_pixmap_directory ("/usr/share/hugo/pixmaps");
  add_pixmap_directory (PACKAGE_DATA_DIR "/pixmaps");
  add_pixmap_directory ("./pixmaps");
  add_pixmap_directory(short_exe_name);
  /*
  add_pixmap_directory (PACKAGE_SOURCE_DIR "/pixmaps");
  */
	
  fileselector_window = create_fileselection1();
  fileselector_cd_path = create_fileselection_cd_path();
  fileselector_cd_system = create_fileselection_cd_system();
  fileselector_rom_path = create_fileselection_rom_path();
	
  input_settings_window = create_window_input_settings();
  about_window = create_window_about();
  general_settings_window = create_general_settings_window();
  manual_window = create_window_manual();
  
  attach_input_signal(input_settings_window);
  
  manual_text = (GtkTextView*)lookup_widget(manual_window, "text_manual");
  
	gtk_text_buffer_insert_at_cursor(gtk_text_view_get_buffer(manual_text),
		manual_content,
		strlen(manual_content));

  get_directory_from_filename(initial_path);
  gtk_file_selection_set_filename( (GtkFileSelection*) fileselector_window, initial_path);

  main_window = create_mainWindow ();
  gtk_widget_show (main_window);

  gtk_main ();
}

static int gui_configuration_index = 0;

static int player_index = 0;

//! Setter for gui_configuration_index
void set_gui_configuration_index(int new_index)
{
	gui_configuration_index = new_index;
	gtk_update_configuration(TRUE);
}

//! Getter for gui_configuration_index
int get_gui_configuration_index()
{
	return gui_configuration_index;	
}

#if defined(ENABLE_NETPLAY)
//! Read a single input mapping for netplay
void
gtk_input_mapping_setting_grab(int slot_number)
{
	GtkOptionMenu* temp_option_menu;
	GtkWidget* temp_widget;
	char tmp_buf[100];
	int index;
	
	sprintf(tmp_buf, "optionmenu_slot%d", slot_number);
	temp_option_menu = (GtkOptionMenu*)lookup_widget(general_settings_window, tmp_buf);
  
  temp_widget = gtk_menu_get_active (GTK_MENU (temp_option_menu->menu));
  index = g_list_index ( GTK_MENU(temp_option_menu->menu)->menu_shell.children, temp_widget);
  
  if ((index > 1) && (index < 7))
  {
  	option.local_input_mapping[slot_number] = index - 2;
  }
  else
  {
  	option.local_input_mapping[slot_number] = -1;  	
  }  
}

//! Seta single input mapping for netplay
void
gtk_input_mapping_setting_set(int slot_number)
{
	GtkOptionMenu* temp_option_menu;
	char tmp_buf[100];
	
	sprintf(tmp_buf, "optionmenu_slot%d", slot_number);
	temp_option_menu = (GtkOptionMenu*)lookup_widget(general_settings_window, tmp_buf);
  
  if (0xFF == option.local_input_mapping[slot_number])
  {
  	gtk_option_menu_set_history(temp_option_menu, 0);
  }
  else
  {
  	gtk_option_menu_set_history(temp_option_menu, option.local_input_mapping[slot_number] + 2);
  }  
}
#endif

//! Read configuration done in the general settings window to alter real variables used in emulation
void
gtk_general_settings_grab()
{
	GtkCheckButton* temp_check_button;
	GtkEntry* temp_entry;
	GtkSpinButton* temp_spin_button;
	GtkOptionMenu* temp_option_menu;
	GtkWidget* temp_widget;
	int i;
	
	// get start at fullscreen mode setting
	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_start_fullscreen");
	option.want_fullscreen = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;

	// want fullscreen aspect?
	temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_maintain_aspect");
	option.want_fullscreen_aspect = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;
	
	// get cd system filename setting
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_cd_system_filename");
	strcpy(cdsystem_path, gtk_entry_get_text(temp_entry));

	// get rom initial path setting
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_rom_basedir");
	strcpy(initial_path, gtk_entry_get_text(temp_entry));	
	
	// get minimal bios setting
	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_minimal_bios");
	minimum_bios_hooking = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;
	
	// get cd path setting
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_cd_path");
	strcpy(ISO_filename, gtk_entry_get_text(temp_entry));	

  // want stereo sound?
  temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_stereo_sound");
  option.want_stereo = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;

	// get output frequency
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_output_frequency");
	option.want_snd_freq = atoi(gtk_entry_get_text(temp_entry));
	
	// get sound buffer size
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_buffer_size");
	sbuf_size = atoi(gtk_entry_get_text(temp_entry));
	
	// get window size
	temp_spin_button = (GtkSpinButton *)lookup_widget(general_settings_window, "spinbutton_window_size");
    option.window_size = gtk_spin_button_get_value_as_int(temp_spin_button);
	
	// get fullscreen height
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_fullscreen_height");
	option.fullscreen_height = atoi(gtk_entry_get_text(temp_entry));

	// get fullscreen height
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_fullscreen_width");
	option.fullscreen_width = atoi(gtk_entry_get_text(temp_entry));

	// get hardware scaling setting
	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_use_overlay");
	option.want_hardware_scaling = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;

	// get arcade card emulation flag
	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_use_arcade_card");
	option.want_arcade_card_emulation = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;

	// get tv size emulation flag
	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_tv_size");
	option.want_television_size_emulation = gtk_toggle_button_get_active( (GtkToggleButton*) temp_check_button) ? 1 : 0;

	// get hardware format setting
	temp_option_menu = (GtkOptionMenu*)lookup_widget(general_settings_window, "optionmenu_overlay_format");
  
  temp_widget = gtk_menu_get_active (GTK_MENU (temp_option_menu->menu));
  switch ( g_list_index ( GTK_MENU(temp_option_menu->menu)->menu_shell.children, temp_widget) )
		{
			case 1:
				option.wanted_hardware_format = SDL_UYVY_OVERLAY;
				break;
			case 2:
				option.wanted_hardware_format = SDL_YUY2_OVERLAY;
				break;
			default:
				option.wanted_hardware_format = 0;
		}

#if defined(ENABLE_NETPLAY)
	// get netplay mode / protocol
	temp_option_menu = (GtkOptionMenu*)lookup_widget(general_settings_window, "optionmenu_netplay");
  
  temp_widget = gtk_menu_get_active (GTK_MENU (temp_option_menu->menu));
  switch ( g_list_index ( GTK_MENU(temp_option_menu->menu)->menu_shell.children, temp_widget) )
		{
			case 2:
				option.want_netplay = LAN_PROTOCOL;
				break;
			case 3:
				option.want_netplay = INTERNET_PROTOCOL;
				break;
			default:
				option.want_netplay = LOCAL_PROTOCOL;
		}
		
	// get cd system filename setting
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_server_hostname");
	strcpy(option.server_hostname, gtk_entry_get_text(temp_entry));	

	// get netplay input mapping
	for (i = 0; i < 5; i++)
	{
		gtk_input_mapping_setting_grab(i);
	}
#endif
}

//! Read current configuration and put the widgets in the corresponding mode
void
gtk_general_settings_set()
{
	GtkCheckButton* temp_check_button;
	GtkEntry* temp_entry;
	GtkSpinButton* temp_spin_button;
	GtkOptionMenu* temp_option_menu;
	char temp_string[10];
	int i;

	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_start_fullscreen");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, option.want_fullscreen ? TRUE : FALSE);

	temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_maintain_aspect");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, option.want_fullscreen_aspect ? TRUE : FALSE);

	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_cd_system_filename");
	gtk_entry_set_text(temp_entry, cdsystem_path);

	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_rom_basedir");
	gtk_entry_set_text(temp_entry, initial_path);

	temp_check_button = (GtkCheckButton*)lookup_widget(general_settings_window, "checkbutton_minimal_bios");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, minimum_bios_hooking ? TRUE : FALSE);

	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_cd_path");
	gtk_entry_set_text(temp_entry, ISO_filename);

	temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_stereo_sound");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, option.want_stereo ? TRUE : FALSE);

	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_output_frequency");
	if (option.want_snd_freq == 0)
		strcpy(temp_string, "");
	else
	  sprintf(temp_string, "%d", option.want_snd_freq);
	gtk_entry_set_text(temp_entry, temp_string);

	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_buffer_size");
	if (sbuf_size == 0)
		strcpy(temp_string, "");
	else
	  sprintf(temp_string, "%d", sbuf_size);
	gtk_entry_set_text(temp_entry, temp_string);	
	
	// set window size
	temp_spin_button = (GtkSpinButton*)lookup_widget(general_settings_window, "spinbutton_window_size");  
	gtk_spin_button_set_value (temp_spin_button, option.window_size);

	// set window width
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_fullscreen_width");
	if (option.fullscreen_width == 0)
		strcpy(temp_string, "640");
	else
	  sprintf(temp_string, "%d", option.fullscreen_width);
	gtk_entry_set_text(temp_entry, temp_string);	

	// set window height
	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_fullscreen_height");
	if (option.fullscreen_height == 0)
		strcpy(temp_string, "480");
	else
	  sprintf(temp_string, "%d", option.fullscreen_height);
	gtk_entry_set_text(temp_entry, temp_string);

	temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_use_overlay");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, option.want_hardware_scaling ? TRUE : FALSE);	

	temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_use_arcade_card");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, option.want_arcade_card_emulation ? TRUE : FALSE);	

	temp_check_button = (GtkCheckButton *) lookup_widget(general_settings_window, "checkbutton_tv_size");
	gtk_toggle_button_set_active( (GtkToggleButton*) temp_check_button, option.want_television_size_emulation ? TRUE : FALSE);	

	temp_option_menu = (GtkOptionMenu *) lookup_widget(general_settings_window, "optionmenu_overlay_format");
	switch (option.wanted_hardware_format)
		{
			case SDL_UYVY_OVERLAY:
				gtk_option_menu_set_history(temp_option_menu, 1);
				break;
			case SDL_YUY2_OVERLAY:
				gtk_option_menu_set_history(temp_option_menu, 2);
				break;
			default:
				gtk_option_menu_set_history(temp_option_menu, 0);
		}

#if defined(ENABLE_NETPLAY)		
	temp_option_menu = (GtkOptionMenu *) lookup_widget(general_settings_window, "optionmenu_netplay");
	switch (option.want_netplay)
		{
			case LAN_PROTOCOL:
				gtk_option_menu_set_history(temp_option_menu, 2);
				break;
			case INTERNET_PROTOCOL:
				gtk_option_menu_set_history(temp_option_menu, 3);
				break;
			default:
				gtk_option_menu_set_history(temp_option_menu, 0);
		}

	temp_entry = (GtkEntry*)lookup_widget(general_settings_window, "entry_server_hostname");
	gtk_entry_set_text(temp_entry, option.server_hostname);

	// get netplay input mapping
	for (i = 0; i < 5; i++)
	{
		gtk_input_mapping_setting_set(i);
	}
#endif
}

#define attach_all_signals(player_number) \
	attach_signal(UP ## player_number);\
	attach_signal(DOWN ## player_number);\
	attach_signal(LEFT ## player_number);\
	attach_signal(RIGHT ## player_number);\
	attach_signal(SELECT ## player_number);\
	attach_signal(RUN ## player_number);\
	attach_signal(I ## player_number);\
	attach_signal(AUTOI ## player_number);\
	attach_signal(II ## player_number);\
	attach_signal(AUTOII ## player_number);\
	attach_signal(PXAXIS ## player_number);\
	attach_signal(PYAXIS ## player_number);\
	attach_signal(PSELECT ## player_number);\
	attach_signal(PRUN ## player_number);\
	attach_signal(PI ## player_number);\
	attach_signal(PAUTOI ## player_number);\
	attach_signal(PII ## player_number);\
	attach_signal(PAUTOII ## player_number);
	

#define attach_signal(input_name) 	temp_button = (GtkButton*)lookup_widget(input_window, "button_" #input_name ); \
	g_signal_connect ((gpointer) temp_button, "clicked", \
		G_CALLBACK (on_button_input_configuration_clicked), \
		#input_name )


//! Attach the signals for input configuration buttons
void attach_input_signal(GtkWidget* input_window)
{
	GtkButton* temp_button;
	
	attach_all_signals(0);
	attach_all_signals(1);
	attach_all_signals(2);
	attach_all_signals(3);
	attach_all_signals(4);

}

//! show the configuration for the current selected configuration
void gtk_update_configuration(gboolean update_joydev)
{
	int player_index = 0;

	//! Added to be sure that SDL can figure out the name of the key
	// Pretty silly IMHO but we have to cope with it
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		SDL_InitSubSystem(SDL_INIT_VIDEO);
	}
		
	printf("Showing configuration #%d\n", gui_configuration_index);
	fflush(stdout);
	
	for (player_index = 0; player_index < 5; player_index++)
	{
		gtk_update_player_configuration(player_index,
			temporary_configuration[gui_configuration_index].individual_config[player_index],
			update_joydev);
	}
	
}

void gtk_update_player_configuration(int player_index,
	individual_input_config individual_configuration,
	gboolean update_joydev)
{
	GtkButton* button = NULL;
	GtkSpinButton* spin_button = NULL;
	int button_index = 0;	
	gboolean enabled_joypad = FALSE;
	
	for (button_index = 0; button_index < J_PAD_START; button_index++)
	{
		sprintf(tmp_buf, "button_%s%d", joymap_reverse[button_index], player_index);
		button = (GtkButton*)lookup_widget(input_settings_window, tmp_buf);
		if (0  != individual_configuration.joy_mapping[button_index])
		{
			sprintf(tmp_buf, "%s", SDL_GetKeyName(individual_configuration.joy_mapping[button_index]));
		}
		else
		{
			sprintf(tmp_buf, "--");
		}
		gtk_button_set_label(button, tmp_buf);
	}

	if (update_joydev)
	{
		sprintf(tmp_buf, "spinbutton_joydev%d", player_index);
		spin_button = (GtkSpinButton*)lookup_widget(input_settings_window, tmp_buf);		
		gtk_spin_button_set_value (spin_button, (double)individual_configuration.joydev);
	}
	
	enabled_joypad = (gboolean)(individual_configuration.joydev > 0);
		
	for (; button_index < J_PXAXIS; button_index++)
	{
		sprintf(tmp_buf, "button_%s%d", joymap_reverse[button_index], player_index);
		button = (GtkButton*)lookup_widget(input_settings_window, tmp_buf);
		if ((0xffff != individual_configuration.joy_mapping[button_index]) && enabled_joypad)
		{
			sprintf(tmp_buf, "But. %d", individual_configuration.joy_mapping[button_index]);	
		}
		else
		{
			sprintf(tmp_buf, "--");
		}
		gtk_button_set_label(button, tmp_buf);
		gtk_widget_set_sensitive((GtkWidget*)button, enabled_joypad);
	}
	
	for (; button_index < J_MAX; button_index++)
	{
		sprintf(tmp_buf, "button_%s%d", joymap_reverse[button_index], player_index);
		button = (GtkButton*)lookup_widget(input_settings_window, tmp_buf);
		if ((0xffff != individual_configuration.joy_mapping[button_index]) && enabled_joypad)
		{
			sprintf(tmp_buf, "Axis %d", individual_configuration.joy_mapping[button_index]);	
		}
		else
		{
			sprintf(tmp_buf, "--");			
		}
		gtk_button_set_label(button, tmp_buf);
		gtk_widget_set_sensitive((GtkWidget*)button, enabled_joypad);		
	}
		
}

//! Creates a surface for grabbing config if no game is running, else grabs it
static void gtk_init_grab_config(char* caption)
{
	SDL_Surface *grab_window;

#if defined(SDL) && !defined(SDL_mixer)
	SDL_PauseAudio(SDL_ENABLE);
#endif

#if defined(SDL_mixer)
	Mix_Resume(-1);
#endif
	
	if (physical_screen == NULL)
        {
        	
        	if (!SDL_WasInit(SDL_INIT_VIDEO))
        	{
        		SDL_InitSubSystem(SDL_INIT_VIDEO);
        	}

	  if ((grab_window = SDL_SetVideoMode(200, 50, 8, 0)) == NULL)
	  {
		fprintf(stderr,"Couldn't create the window for grabbing key\n");
		Log("Couldn't create the window for grabbing key\n");
	  }
	  SDL_WM_SetCaption(caption, NULL);
	}
	else
	{
	  grab_window = physical_screen;
	}

	if (SDL_WM_GrabInput(SDL_GRAB_ON) != SDL_GRAB_ON)
	  printf("Couldn't grab input focus.\n");	
}

//! Releases the capture surface used for grabbing configuration
static void gtk_close_grab_config()
{
	if (physical_screen == NULL)
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}					

	if (SDL_WM_GrabInput(SDL_GRAB_OFF) != SDL_GRAB_OFF)
	  printf("Couldn't release window focus.\n");

#if defined(SDL) && !defined(SDL_mixer)
	SDL_PauseAudio(SDL_DISABLE);
#endif

#if defined(SDL_mixer)
	Mix_Pause(-1);
#endif
	
}

//! Read the value of a pressed key when asked for a new value in the configuration change
UInt16 gtk_grab_config_for_key()
{
	SDL_Event event;
	UInt16 result_value = 0;

	gtk_init_grab_config("Press a key");

	while (SDL_WaitEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
				{	
					result_value = (SDLK_ESCAPE == event.key.keysym.sym)
						? 0 : event.key.keysym.sym;
					break;
				}
		}

	gtk_close_grab_config();

	return result_value;

}

//! Read the value of a pressed joypad button when asked for a new value in the configuration change
UInt16 gtk_grab_config_for_pad_button(int joypad_index)
{
	SDL_Event event;
	UInt16 result_value = 0;

	sprintf(tmp_buf, "Press a button of %s", SDL_JoystickName(joypad_index));
	gtk_init_grab_config(tmp_buf);

	while (SDL_WaitEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (SDLK_ESCAPE == event.key.keysym.sym)
				{
					result_value = -1;
					break;
				}
			}
						
			if (event.type == SDL_JOYBUTTONDOWN)
				{										
					
					if (event.jbutton.which == joypad_index)
					{
						printf("Grabbed button %d\n", event.jbutton.button);
						result_value = event.jbutton.button;
						break;
					}
				}
		}

	gtk_close_grab_config();

	return result_value;

}

//! Read the value of a pressed joypad axis when asked for a new value in the configuration change
UInt16 gtk_grab_config_for_pad_axis(int joypad_index)
{
	SDL_Event event;
	UInt16 result_value = 0;

	sprintf(tmp_buf, "Move an axis of %s", SDL_JoystickName(joypad_index));
	gtk_init_grab_config(tmp_buf);

	while (SDL_WaitEvent(&event))
		{
			
			if (event.type == SDL_KEYDOWN)
			{
				if (SDLK_ESCAPE == event.key.keysym.sym)
				{
					result_value = -1;
					break;
				}
			}
						
			if (event.type == SDL_JOYAXISMOTION)
				{
										
					if (event.jaxis.which == joypad_index)
					{
						if ((event.jaxis.value < -16384) || (event.jaxis.value > 16383))
						{							
							printf("Grabbed axis %d (value %d)\n", event.jaxis.axis, event.jaxis.value);
							result_value = event.jaxis.axis;
							break;
						}
					}
				}
		}

	gtk_close_grab_config();

	return result_value;

}


//! Copy the current configuration to the temporary one
void gtk_copy_current_configuration()
{
	memcpy(temporary_configuration, config, 16 * sizeof(input_config));
	gtk_update_configuration(TRUE);
}

//! Copy back the temporary configuration into the reference one
void gtk_confirm_configuration()
{
	memcpy(config, temporary_configuration, 16 * sizeof(input_config));
}

//! Grab the value for the given 'direction' and the given player
void gtk_grab_control(int direction_index, int player_number)
{
	if (direction_index < J_PAD_START)
	{
		// It's a simple key we're looking for
		temporary_configuration[get_gui_configuration_index()].
			individual_config[player_number].joy_mapping[direction_index] =
			gtk_grab_config_for_key();
	}
	else
	{
		if (direction_index < J_PXAXIS)
		{
			// It is a joystick button
			temporary_configuration[get_gui_configuration_index()].
				individual_config[player_number].joy_mapping[direction_index] =
				gtk_grab_config_for_pad_button(
					temporary_configuration[get_gui_configuration_index()].
						individual_config[player_number].joydev - 1);
		}
		else
		{
			// It is a joystick axis
			temporary_configuration[get_gui_configuration_index()].
				individual_config[player_number].joy_mapping[direction_index] =
				gtk_grab_config_for_pad_axis(
					temporary_configuration[get_gui_configuration_index()].
						individual_config[player_number].joydev - 1);			
		}
	}
	gtk_update_configuration(FALSE);	
}

void set_gui_joydev(int player_number,int new_value)
{
	temporary_configuration[get_gui_configuration_index()].
		individual_config[player_number].joydev = new_value;
	printf("joydev[%d] = %d\n", player_number, new_value);
}
