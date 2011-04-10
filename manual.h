static char manual_content[] = "\
Hu-Go! Quickstart\n\
\n\
[mail:zeograd@zeograd.com||Zeograd]\n\
\n\
Table of Contents\n\
\n\
Introduction\n\
Keyboard mapping\n\
    Games keys\n\
    Special keys\n\
Supported formats\n\
Options\n\
    Graphics\n\
    Paths\n\
    CD emulation\n\
    Sound\n\
    Netplay\n\
\n\
\n\
\n\
 Introduction\n\
\n\
This document briefly describes how to play pc engine \n\
games with Hu-Go!. More detailled explanations can be \n\
found in the other thematic document in the same \n\
directory as this one.\n\
\n\
Hu-Go! can be launched without argument to start with a \n\
gtk interface in which you can change options and start \n\
roms and cds. You can also start it giving as argument \n\
the name of the .pce file to run.\n\
\n\
 Keyboard mapping\n\
\n\
 Games keys\n\
\n\
By default, the keyboard is mapped like this :\n\
\n\
up up arrow\n\
\n\
down down arrow\n\
\n\
left left arrow\n\
\n\
right right arrow\n\
\n\
II button Alt key\n\
\n\
I button Space key\n\
\n\
select Tab key\n\
\n\
run Return key\n\
\n\
auto II X key\n\
\n\
auto I C key\n\
\n\
 Special keys\n\
\n\
Toggle fullscreen F9 key\n\
\n\
Quit F12 key / ESC key\n\
\n\
Save current game state F6 key\n\
\n\
Load current game state F7 key\n\
\n\
 Supported formats\n\
\n\
You can use the \"load rom\" button to load rom as .pce \n\
files, or cd as .iso files. The \"load cd\" button is used \n\
to play real pc engine cds.\n\
\n\
 Options\n\
\n\
Options control how the game are rendered. They are \n\
stored in an .ini file which is generated from the gtk \n\
interface (prefered) or edited with a text editor. Most \n\
options can be overriden with command line options.\n\
\n\
 Graphics\n\
\n\
 Start games in fullsceen mode : When game are started, \n\
  they are in fullscreen mode.\n\
\n\
 Maintain pce aspect ratio in fullscreen mode : When in \n\
  fullscreen mode, keep the same ratio for screen \n\
  dimention than the one of the original game, else use \n\
  the maximum available space even if it means that \n\
  proportions are messed.\n\
\n\
 Emulate television size [Not yet implemented] : Drop \n\
  the rendering of lines outside the 224 lines of the \n\
  middle of the screen. When using games on tv, those \n\
  are generally outside the visible area.\n\
\n\
 Window zoom factor : Zoom factor when in windowed mode.\n\
\n\
 Prefered full screen size : Size of the fullscreen \n\
  mode. You can switch to it with F9 key.\n\
\n\
 Hardware acceleration when available : Try to use the \n\
  super fast hardware rendering mode. It is not \n\
  available on older machines, and will simply use the \n\
  classical mode in this case.\n\
\n\
 Hardware graphic format : Change this value to \n\
  something else than Autodetect if colors are screwed \n\
  when using the hardware acceleration.\n\
\n\
 Paths\n\
\n\
 CD system filename : Path to the cd system rom to be \n\
  used for launching cd or isos.\n\
\n\
 Default rom directory : Directory in which to begin \n\
  browsing roms.\n\
\n\
 CD emulation\n\
\n\
 Soft bios emulation mode : Do not try to emulate cd \n\
  bios calls at high level, hence slowing the cd \n\
  emulation but raising the compatibility.\n\
\n\
 CD path [Unused for windows] : Path to the cd rom \n\
  device, e.g. /dev/hdd.\n\
\n\
 Enable arcade card mode [Still in progress] : Enable \n\
  arcade card emulation.\n\
\n\
 Sound\n\
\n\
 Use stereo sound : Enable stereo sound rendering.\n\
\n\
 Output frequency : Frequency of sound rendering. If \n\
  your card doesn't support the given frequency, Hu-Go! \n\
  will pick the nearest supported one.\n\
\n\
 Buffer size : Size of the buffer sound. You can double \n\
  or half it if the sound is choppy. 256, 512 or 1024 \n\
  should fit most machines. It must be a power of 2.\n\
\n\
 Netplay\n\
\n\
 Netplay mode : \"Local mode\" disables netplay support \n\
  while \"LAN netplay\" enables it using the LAN protocol \n\
  and \"INTERNET netplay\" enabled it using the Internet protocol.\n\
\n\
 Server hostname [Unused when in local mode] : Hostname \n\
  of the machine running the Hu-Go! netplay server. It \n\
  doesn't support ip for now.\n\
\n\
 Server port [Unused when in local mode] : Port on \n\
  which the Hu-Go netplay server is listening.\n\
\n\
 Slot X [Unused when in local mode] : Number of the \n\
  local input to export for netplay. \"None\" should be \n\
  used for the last entries. Typical configuration is \"\n\
  Slot 1 : Player 1\" and remainings to \"None\"\n\
";
