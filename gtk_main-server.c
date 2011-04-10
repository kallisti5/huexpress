/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "gtk_main-server.h"
#include "interface-server.h"
#include "config.h"

GtkWidget* window_main;
GtkWidget* window_help;
gboolean gtk_stop_asked;

//! Construct the gtk interface
void build_gtk_interface (int argc, char* argv[])
{
	
  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (".");
  add_pixmap_directory ("/usr/share/hugo/pixmaps");
  add_pixmap_directory (PACKAGE_DATA_DIR "/pixmaps");
  add_pixmap_directory ("./pixmaps");
	
  window_main = create_window_main();
  window_help = create_window_help();

  gtk_widget_show (window_main);

  gtk_main ();
}

//! Append string to the buffer
void printf_screen (char *format, ...)
{
  char buf[256];
  GtkTextView* textview_status = NULL;
  GtkTextMark* insert_mark = NULL;

  va_list ap;
  va_start (ap, format);
  vsprintf (buf, format, ap);
  va_end (ap);

  if (window_main)
    {
      textview_status = (GtkTextView*) lookup_widget(window_main, "textview_status");
      if (textview_status)
	{
	  gtk_text_buffer_insert_at_cursor(gtk_text_view_get_buffer(textview_status),
					   buf,
					   strlen(buf));
	  insert_mark = gtk_text_buffer_get_mark (gtk_text_view_get_buffer(textview_status),
						  "insert");
	  gtk_text_view_scroll_to_mark    (textview_status,
					   insert_mark,
					   0.0f,
					   FALSE,
					   0.0f,
					   0.0f);
	  return;
	}
    }
  
  vprintf(format, ap);

}
