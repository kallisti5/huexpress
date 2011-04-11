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

#include "hugod.h"

#include <stdlib.h>
#include <stdio.h>
#include "netplay.h"
#include <getopt.h>
#include "gtk_main-server.h"

#define DEBUG

#if defined(GTK)
static const int GTK_SERVER_SOCKET_RATIO = 100;
static int gtk_iteration = 1;
#endif

#if !defined(GTK)
void printf_screen (char* format, ...)
{
  char buf[256];
  GtkTextView* textview_status = NULL;

  va_list ap;
  va_start (ap, format);
  vsprintf (buf, format, ap);
  va_end (ap);

  vprintf(format, ap);
}
#endif


/*!
 * Sets the global options from the command line arguments
 * \param argc number of command line arguments
 * \param argv content of command line arguments
 * \param global_option pointer to the global option structure
 * \return 0 in case of success
 */
int
read_arguments (int argc, char *argv[], global_option_type * global_option)
{
  int option;

  for (;;)
    {
      option = getopt (argc, argv, "p:P:il");

      if (option == -1)
	{
	  break;
	}

      switch (option)
	{
	case 'p':
	  if ((atoi (optarg) >= MAX_NUMBER_PLAYER)
	      || (atoi (optarg) < MIN_NUMBER_PLAYER))
	    {
	      printf_screen ("Error: invalid number of players (%d not in [1-5])\n",
			     atoi (optarg));
	      return 1;
	    }
	  printf_screen("Opening %d slot%s\n", atoi(optarg), atoi(optarg) > 1 ? "s": "");
	  global_option->number_player = atoi (optarg);
	  break;
	case 'P':
	  global_option->server_port = atoi (optarg);
	  break;
	case 'i':
	  printf_screen("Setting INTERNET protocol\n");
	  global_option->type_server = INTERNET_PROTOCOL_TYPE;
	  break;
	case 'l':
	  printf_screen("Setting LAN protocol\n");
	  global_option->type_server = LAN_PROTOCOL_TYPE;
	  break;
	case '?':
	  // getopt already output an error version, it's enough
	  break;
	default:
	  printf_screen("Unknown command line option : %c\n", option);
	  break;
	}
    }

  return 0;

}

/*!
 * Side effect free minimum computation
 */
static int
min (int lhs, int rhs)
{
  return (lhs < rhs) ? lhs : rhs;
}

/*!
 * main loop. Accept contribution from clients and dispatch digest of
 * the frame to all clients
 */
void
serve_dispatch (global_option_type * global_option)
{

  global_status_type global_status;
  int client_index;

  /*
   * Initialize global_status fields
   */
  global_status.frame_number = 1;
  global_status.number_identified_players = 0;
  global_status.number_allocation_request = 0;
#if defined(GTK)
	gtk_stop_asked = FALSE;
#endif

  for (client_index = 0; client_index < MAX_NUMBER_PLAYER; client_index++)
    {
      global_status.player_status[client_index] = UNIDENTIFIED;
    }

  global_status.server_socket = SDLNet_UDP_Open (global_option->server_port);
  if (global_status.server_socket == NULL)
    {
      printf_screen ("Couldn't open UDP socket on port %d.\nCheck privileges and availability.\n",
		     global_option->server_port);
      return;
    }

  /* global_status.server_socket is ready to serve our needs :) */

  global_status.current_packet = SDLNet_AllocPacket (CLIENT_PACKET_SIZE);

  if (global_status.current_packet == NULL)
    {
      SDLNet_UDP_Close (global_status.server_socket);
      printf_screen ("Failed to allocate a buffer for receiving client packets (size: %d bytes) (Not enough memory ?)",
		     CLIENT_PACKET_SIZE);
      return;
    }

  global_status.digest_packet = SDLNet_AllocPacket (SERVER_PACKET_SIZE);

  if (global_status.digest_packet == NULL)
    {
      SDLNet_UDP_Close (global_status.server_socket);
      SDLNet_FreePacket (global_status.digest_packet);
      printf_screen ("Failed to allocate a buffer for sending packets (size: %d bytes) (Not enough memory ?)",
		     SERVER_PACKET_SIZE);
      return;
    }

  /* Allocate enough space for a single socket */
  global_status.server_socket_set = SDLNet_AllocSocketSet (1);

  if (global_status.server_socket_set == NULL)
    {
      SDLNet_UDP_Close (global_status.server_socket);
      SDLNet_FreePacket (global_status.current_packet);
      SDLNet_FreePacket (global_status.digest_packet);
      printf_screen ("Couldn't allocate a socket set (not enough memory ?).\n");
      return;
    }

  if (SDLNet_UDP_AddSocket (global_status.server_socket_set, global_status.server_socket) !=
      1)
    {
      SDLNet_UDP_Close (global_status.server_socket);
      SDLNet_FreePacket (global_status.current_packet);
      SDLNet_FreePacket (global_status.digest_packet);
      SDLNet_FreeSocketSet (global_status.server_socket_set);
      printf_screen ("Error when adding socket to socket set.\n");
      return;
    }

  /* Identification loop */

  /*
   * We're expecting identification packets until we've filled all slots, then
   * we can proceed to the real meat
   */

  for (;;)
    {

      int number_ready_socket;

#if defined(DEBUG)
      printf_screen ("Waiting for identification\n");
#endif

      
      if (read_incoming_server_packet (&global_status))
	{
	  identify_client (&global_status, global_option);
	  
	  if (count_remaining_slot (&global_status, global_option) == 0)
	    {
	      /* Perfect, we've finished the identification of all slots */
	      break;
	    }
	  
	  printf_screen("%d slots open.\n", count_remaining_slot (&global_status, global_option));
	  
	  /* Going back to the identification loop */
	  continue;
	  
	}

#if defined(GTK)

      gtk_iteration = GTK_SERVER_SOCKET_RATIO;

      do {
	number_ready_socket =
	  SDLNet_CheckSockets (global_status.server_socket_set, SERVER_SOCKET_TIMEOUT / GTK_SERVER_SOCKET_RATIO);
	  
	while (gtk_events_pending())
	{
	  if (gtk_main_iteration())
	  {
	  	gtk_stop_asked = TRUE;
	  }
	}
      } while ( (number_ready_socket == 0) && (--gtk_iteration != 0) && !gtk_stop_asked);
#else

      number_ready_socket =
	SDLNet_CheckSockets (global_status.server_socket_set, SERVER_SOCKET_TIMEOUT);      

#endif

	if (gtk_stop_asked)
	{
		break;
	}

      if (number_ready_socket == -1)
	{
	  printf_screen ("Error in socket waiting (disconnection ?).\n");
	  break;
	}

      if (number_ready_socket == 1)
	{

#if defined(DEBUG)
	  printf_screen ("Got a packet\n");
#endif

	  /* We're awaiting a packet in the server socket */
	  if (read_incoming_server_packet (&global_status))
	    {

	      /*
	       * If we haven't identified all clients yet, we're trying to use the current packet
	       * to improve our knowledge of the typography
	       */
	      identify_client (&global_status, global_option);
	      
	      if (count_remaining_slot (&global_status, global_option) == 0)
		{
		  /* Perfect, we've finished the identification of all slots */
		  break;
		}

	      printf_screen("%d slots open.\n", count_remaining_slot (&global_status, global_option));

	    }
    }

	
	}

	if (!gtk_stop_asked)
	{

  printf_screen ("Identification finished\n");

#if defined(DEBUG)
  for (client_index = 0; client_index < MAX_NUMBER_PLAYER; client_index++)
    {
      printf_screen ("Mapping[%d] = { { 0x%08X, %d }, %d }\n", client_index,
		     global_status.input_mapping[client_index].address.host,
		     global_status.input_mapping[client_index].address.port,
		     global_status.input_mapping[client_index].remote_input_device);
    }
#endif

  switch (global_option->type_server)
    {
    case LAN_PROTOCOL_TYPE:
      serve_clients_lan_protocol(&global_status, global_option);
      break;
    case INTERNET_PROTOCOL_TYPE:
      serve_clients_internet_protocol(&global_status, global_option);
      break;
    default:
      printf_screen("Internal error, unknown internal server type : %d\n", global_option->type_server);
      break;
    }
  } // gtk_stop_asked
      
  /*
   * Free resources
   */
  SDLNet_FreePacket (global_status.current_packet);
  SDLNet_FreePacket (global_status.digest_packet);
  SDLNet_FreeSocketSet (global_status.server_socket_set);
  SDLNet_UDP_Close (global_status.server_socket);
  global_status.server_socket = NULL;

}

int
main (int argc, char *argv[])
{
  global_option_type global_option;	//!< Application global options

  global_option.server_port = DEFAULT_SERVER_PORT;
  global_option.number_player = MAX_NUMBER_PLAYER;
  global_option.type_server = LAN_PROTOCOL_TYPE;

#if defined(DEBUG)
  fprintf (stderr, "DEBUG mode is ON\n");
#endif

  if (read_arguments (argc, argv, &global_option) != 0)
    {
      fprintf (stderr, "Error reading arguments\n");
      return 2;
    }

  if (SDL_Init (0) == -1)
    {
      fprintf (stderr, "SDL_Init: %s\n", SDL_GetError ());
      return 1;
    }

  if (init_network () != 0)
    {
      fprintf (stderr, "Error initializing network\n");
      return 1;
    }

#if defined(GTK)

	if (argc == 1)
	{
		// No option given starts the GUI
		build_gtk_interface(argc, argv);
		return;
	}

#endif
  
  serve_dispatch (&global_option);

  shutdown_network ();

  SDL_Quit();

  return 0;
  
}
