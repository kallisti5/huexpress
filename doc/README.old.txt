            .  ___   ____                _________           ___
             .|  `|_|   `| ___ ___  __ .|    ____/ _______ .|  `|
           .:|     _     ||  `|  `|(__)|    (_  `|/   _  `\|____/:.
      ...:::||____|:|____||_______/::::\_________/\_______/(____)::::...
            `-*-- -  -   -    -      -            -              ^cls
                Core-GraphX / PC Engine / Turbo GraphX Emulator
                             Version 2.11
           


       THIS MANUAL IS DEPRECATED. IT ONLY REMAINS FOR ARCHEOLOGISTS !!!



        N.B. When reading this .TXT - "(*)" indicates the main changes

--[ CONTACT INFORMATION ]----------------------------------------------------
    E-Mail :   zeograd@zeograd.com 

    ICQ UIN :  40632933

    Homepage : http://www.zeograd.com


--[ DISCLAIMER ]-------------------------------------------------------------

    I can't be held responsible for any misuse of this software, it comes
    with absolutely no warranty. Use it at your own risks.

--[ INTRODUCTION ]-----------------------------------------------------------

    Hi everyone, Welcome to the Hu-Go! documentation.
    I (Zeograd) am not really the author of this program. I discovered
    sources of a PC Engine emulator at Bero's Homepage
    (http://www.geocities.co.jp/Playtown/2004/)

    Plus improvements at Hmmx's Homepage
    (formerly, http://www.geocities.co.jp/SiliconValley/7052/).

    Hmmx made XPCE (for DirectX) but I've been interested in continuing
    their work under DOS and voila, you've got another emulator available
    to burn your keyboard playing all night with great PCE games ;)

    This one is free as in free speech, you hence have access to sources.
    I'd like people interested in making a good emulator for free to
    contact me to talk about what is missing in Hu-Go!. Don't hesitate
    to use the bugzilla and forum facilities or mail me.

--[ HOW TO INSTALL IT ? ]----------------------------------------------------

    Hu-Go! is now available in binary form for several platforms, such as
	Microsoft windows, i386 debian, i386 Mandrake. In those cases, follow
	the custom instructions for your OS. Hu-Go! is also available as
	sources. There are directly compilable for Linux, Microsoft windows,
	Solaris 8+, FreeBsd and with some work for any Un*x, BeOs, ...
	
	Check the INSTALL file for further instructions concerning the source
	distribution.
	
--[ HOW TO USE IT ? ]--------------------------------------------------------

    You can hardly make it easier (maybe with a direct synaptic link between
    your brain and your computer to guess the name of the rom...) :
	Just type hugo with no options to bring the gtk gui which is quite straight
	forward. You can load a rom (or .iso) or fire a cd. You can load and save
	file using the menu, or change the settings, which are those you can change
	in the .ini file.
    You can also use hugo without the gui, just type
	hugo [ROM] [BACKUPMEM] [OPTION] where ROM is the name of the
    ROM or ISO or ISQ or HCD. Check out the HCD section later for details.
    you want to play with. If ROM has no extension, Hu-Go!
    will look for ROM.PCE then ROM.ZIP. If the ROM has PCE extension, try it,
    then try ROM in ROM.ZIP. Then if ROM has ZIP extension, look for the
    PCE file with same basename as ROM...
    ISO games must be specified with ISO extension to be recognized.

    (Recommended games - try SUPER STAR SOLDIER or NEUTOPIA 2, you won't
    regret it!. If you don't have any rom, you can freely download some
    made with Huc [www.zeograd.com])

    For OPTIONS, see later...

    BACKUPMEM is the name of the file containing the backup RAM.
    These two last are optionals. The order shouldn't import but the ROM name
    must be before the name of backup RAM.

--[ HOW TO CONFIGURE HU-GO! FOR PLAYING CDS ? ]------------------------------

	Under linux, you first have to configure the cd path (ie /dev/cdrom or such)
	either on the command line (-i <cd path>), the .ini file (variable cd_path),
	or in the gui, under the tab 'CD emulation'.
	FreeBSD and Solaris doesn't have yet the CD support.
	For any platform, choose the system card rom location. It's the rom which
	actually boots the CD, and it's called syscard.pce or such. As for all
	commercial roms, you can only use it if you've bought a system card hucard
	or an hardware containing it (Any duo for instance).
	It's a known bug that you can't always play several CDs in a row without
	restarting the whole emulator.

--[ SYSTEM REQUIREMENTS ]----------------------------------------------------

    -- Pentium 166 (maybe less without sound; something like 233 or 266 for
       good sound).

    -- 8MB of RAM.

    -- A Linux system or FreeBSD or Microsoft windows (only 95 to XP tested)

    -- A sound card (only if you want to hear sound, of course).

    -- A small amount of brain cells (enough to control basic motor
       functions. For Cheating and Disassembling, a few trillion more may be
       required ;)

    -- Fingers (may be replaced by a direct synaptic link, I'm working on it,
       if you want to become a guinea pig, let me know too ;) Note - requires
       brain cells specified above.

--[ KEYBOARD CONTROLS ]------------------------------------------------------

    Cursor keys          Direction
    Alt                  Button 1
    Space                Button 2
    Tab                  Select key
    Enter                Start key
    X                    Toggle Autofire 1
    C                    Toggle autofire 2

    (These are default keys for all players)
    You can edit yours using the HU-GO!.INI (dos/windows) or hugo.ini (un*x)
	file (See details later)

    Special keys:

    Can't be changed (you can always assign these keys to "normal" ones,
    it will mostly have the "special" effects, eventually followed by the
    "normal" ones)
    

    tilde key (under ESC key)   Display the number of frame elapsed
             since the beginning of the track (to create subtitles)
    1 on alpha pad   Toggle the sprites display
    2 on alpha pad   Toggle the background display

-- alpha keys --
   3,4,5,6,7 and 8 on alpha pad
                     May unblock some isos
-- alpha keys --

    - on alpha pad   Lower the sound level
    = on alpha pad   Raise the sound level
    9 on alpha pad   Lower the sound quality
    0 on alpha pad   Raise the sound quality
    F1               Enter a value to search for (See details later)
    F2               Set a value in RAM (See details later)
    F3               Freeze a value in RAM (See details later)
    F4               Test purpose key, now display the draft gui
    F5               Save ScreenShot (named pict????.pcx) (disabled right now)
	F9				 Toggle full screen mode
    ESC, F12         Exit (not really useful)
    F6               Save game progression (named ROM.SAV where ROM is the
                     ROM name, Also work for iso file in file names ISO.SVI,
                     For games on CD, only 1 saved game is allowed, whatever the CD)
    F7               Load game progression
    'Num Lock'       Toggle sound dumping mode

    Keys Used on Numeric Keypad
    /                Toggle image dumping mode (in VIDEO/*.PCX)
    +                Skip one more frame per sec.
    -                Skip one less frame per sec.

--[ OPTIONS ]----------------------------------------------------------------

    There are two kinds of options. Command line or HU-GO!.INI options. The
    emu first reads in the INI file then the command line, so you can
    over-ride general options.

    ** Command line options
    Can be either -FV or -F V where F is the flag and V the value

   -- c : CD emulation (This way of emulating ISO is no more compulsory but still works,
                         is compulsory for using CDs)
        0 -> Only Hu-card emulation (Default)
        1 -> CD emulation on
        2 -> ISO file emulation on
        3 -> ISQ file emulation on
        4 -> BIN file emulation on (it's a raw full dump, only 1 track supported
          right now, and only if <280 Mb)
		  
	-- f : Fullscreen model
		0 -> Start in window mode
		1 -> Start in fullscreen mode

    -- m : No bios mode
        0 -> Use bios as much as possible (Default, faster but sometime less
                                           accurate)
        1 -> Use no bios at all as possible (slower but make more game works)

	-- s : Stereo mode
		0 -> Mono mode (Default)
		1 -> Stereo mode

    -- u : US encoded rom
        0 -> Normal rom (Default)
        1 -> US encoded rom, with invertion of bits
       Hu-Go! should automaticaly recognize such rom but if not (i.e.
       it works only is -u1 is specified) tell me so that I can add it
       to the database.
	
	-- w : Window size multiplier
		1 -> normal window size (Default)
		2 -> doubled window size
		3 -> tripled window size
		4 -> the meaning of this option is let to the reader's attention		

    ** Initialisation file options
    This file accepts comments in lines beginning with a #, the form is
    F=V where F the name of the option and V the value.

    --KEYS : it's a bit long to explain in details but I'll explain the
    method. Each function is represented by a string ("UP","DOWN","LEFT",
    "RIGHT","I","II","SELECT","START","AUTOI","AUTOII") immediately followed
    by the number of the contoller. The value is then the scancode as you
    can find it in the SCANCODE.TXT.
    When mapping a joypad related configuration, you can also use "PI","PII",
   "PSELECT", "PSTART", "PAUTOI", "PAUTOII" to map button I, II, Select, Start
    and autoI, autoII. The given value of the right being the number of the
    button on your pad, of course.
    Now, you can create up to 15 different configs by using sections like
    [config5]. These sections must be at the end of the INI files. They
    contain key definitions as explained above but also info on controllers
    e.g. putting input2=key3 will make the 2nd pad of the PC Engine to be
    controlled by the 3rd keyboard mapping (UP3, LEFT3,...). As valid strings
    you have 'input1' to 'input5' for the 5 PC Engine Gamepads (only 4
    emulated so far), and 'key1' to 'key5' for 5 key mappings, 'joy1' to
    'joy4' for 4 different joypads, 'mouse1' and 'mouse2' for 2 mice (not yet
    implemented) and 'synaplink' for a direct synaptic link (also not
    implemented ;)

    E.G. :
    Setting in the INI file

     config=1

     [config1]

       input1=key1

       UP1=0x16
       LEFT1=0x23
       DOWN1=0x24
       RIGHT1=0x25

       input2=joy1

    This will change direction keys for the first player to 'u','h','j','k'
    while the second player will play with the first joypad. Note that when
    you specify a joy input, only the directions and the 2 buttons are
    remapped so you can still choose keys for select, start, autoI and
    autoII. As an example, the config1 is just a standard input with 1 player
    using a joypad so if you want to play with a joypad just uncomment the
    line with config=1. It's not very clear but the built-in menu allows easier
	configuration.

    -- language : Language of most messages during the emulation
          0 -> English (default) (by me)
          1 -> Francais (by me)
          2 -> Espanol (by my gf, and Juan roman Soriano)
          3 -> Slovensko (by ]pit[ )
          4 -> Portuguese (by CodeMaster)
          5 -> German (by sALTY)
          6 -> Dutch (by Fixo)
          7 -> Polish (by Dox and Faust)
          8 -> Italian (by Gareth Jax)
		  9 -> Russian (by Lord Mardulak)

    -- rom_dir : Directory of your roms. It's the default directory the
    fileselector will look in. Use either '/' or '\'.
    (If no value given, current path is assumed)

    -- snd_freq : Frequency of the PCM sound output. The higher, the best
    quality but the slower. Use 11025 on slow machines and 22050 or 44100
    on fast machines. You can also give intermediate values.
       22050 Hz is default

    -- buffer_size : Size of the buffer used for PCM sound output. the best
    I can tell you here is to make tests. All depends of the frequency you use
    and your machine speed. 256 bytes is the default (Fine for XP1900+) you can
	also try 512 or 1024 if you got sound which stops at times.
	
	-- cd_path : Device name of the cd drive under UN*X systems.
	   /dev/cdrom is default
	   
	-- stereo : Whether to output sound in stereo.
	   0 -> Mono sound (Default)
	   1 -> Stereo sound
	   
	-- fullscreen_width : Preferred width of fullscreen mode
	   640 is the default
	   
	-- fullscreen_height : Preferred height of fullscreen mode
	   480 is the default
	   
	-- window_size : Zoom factor when in windowed mode
	   1 to 4 are valid zoom factor (1 being the default)
	   

--[ HCD ]--------------------------------------------------------------------

   Then what is this new format.
   HCD means : Hu-Go! Cd Definition. Such a file allow you to use multi-code
   CDs and emulate audio tracks with MP3
   It's only a beginning and there are still troubles with ISQ to emulate
   Code tracks but it should work fine later.
   HCD are divided in sections :
   [main]
   for main info :
   first_track=XX
   last_track=XX

   that indicates the first and last track (easy)

   ISO_path=XXX
   MP3_path=XXX

   which are the default path for ISO and MP3 files, convenient when moving
   of directory e.g.
   If you don't specify anything there, the default path is the .HCD one

   minimum_bios=X

   where X is 0 or 1. Use to enable this mode (see in command line option)
   when launching a particular HCD. (Now, this mode is 'no bios' but for
   obvious compatibility reason, I've not changed the name...)

   Then for each track you can find a section :
   [trackXX]
   where you'll find :

   filename=...

   i.e. the filename of the file to use to emulate this track (.ISO or .ISQ
   for code or .MP3 for audio)
   then :

   type=CODE

   that specify if the track is a code one (audio is default)
   et finally

   begin=lsn,XXX

   to specify the beginning of the track in LSN format (# of sector since the
   beginning of the first one) or LBA (# of sector since the beginning of the
   CD) or MSF (theoricaly, only LSN really tested) (as for MSF, just do :
   begin=msf,mm:ss:ff
   add zeros if compulsory)
   even if just a beginning, it allows playing multi-code tracks
   and MP3 in games. (even if .MP3 control isn't yet perfect)
   You'll find an example in the archive.

   There's now another mode available. It's the cd one.
   Write
   type=CD
   and you'll have the ability to fake a track from the .hcd file with a
   track coming from a real cd.
   In this mode, you have 2 mode fields:
   drive=0
   which specify the drive in which is the track you want to use, using the
   format in which the cd driver is used to. i.e. 0, 1 and such.. for aspi
   driver and letter D, E, and such for the mscdex driver.

   Then you can specify the number of the track to use on the cd driver with
   track=5
   If you don't specify this field, the default value for the track field will
   be the track number of the track to fake.


   You can also use patching functions

   patch_number=XX

   where XX is the number of patch you want to apply

   then

   patchX=0X????????,0X??

   where X goes from 0 to patch_number-1 and two hexa numbers represent
   the offset and new val of the patch in the ISO file.

   On the same model, you can also find a way of adding subtitle when audio
   tracks are played (even if you don't own the MP3 for it). You can choose
   the number of subtitles with : 
   
   subtitle_number=XX
   
   where XX is the number of subtitle you want to have for the track.

   You can also choose to synchronize the subtitles with the game or the
   music with

   synchro_mode=XX

   if XX = 0, synchronisation is done with the game as in the first release
   supporting it, else it's synchronised with music and you can replace
   the words 'number of frame' by '60th of sec' in the following explanation,
   concerning the meaning of the begin field.

   Then, for each subtitle, you must choose the time where it should begin,
   its duration and the message to display.
   The syntax is as follow :
   
   subtitleXX=<begin>,<duration>,<message>
   
   where XX is the number of the subtitle (XX is between 0 and subtitle_number-1)
   <begin> is the number of frame elapsed since the beginning of the track.
   There's normally 60 frame per sec but using the number of frame instead
   of time make subtitles synchronized with the real game and not the music.
   Since it's harder to guess how many frame have been displayed, I've added
   a display of such a number with the tilde key. The value that you'll see
   when pressing the key is the exact value you'll have to put in the <begin>
   field (ajusting them a bit if needed...)
   The <duration> field is in 60th of second, i.e. putting 60 there will
   display the message for 1 sec and finally, the last field is the message
   that will be displayed. It shouldn't contain any comma.
   One last thing : you must sort the subtitle according to the order of
   appearition.
   Don't hesitate looking at the example or sending a mail if needed.

--[ CHEATING ]---------------------------------------------------------------

    I've pondered at length as to whether to include such an option. If I'm
    not mistaken, Hu-Go! is the first emulator to propose this type of
    option. Cheating is very primitive and there is no visual help so you
    can't see what you type...

    BUT...

    It works! If you want to cheat with the number of lives in a game,
    first you run your game, then you type F1, the game stops. This is
    normal. It's waiting for the value to search. Then you enter the number
    of lives you actually have (In fact, it only considers the lower byte of
    the value you entered), then it makes a search and shows you the result.
    Play around and lose a life, repeat the same as above, pressing F1 and
    entering the current value. Repeat it again and again until the search
    only finds one value..
    Note carefully this value, it's the offset in RAM of a variable that
    contains the value you've entered. Is it the correct value? Easy, press
    F2, the game stops then enter the offset noted before and the new value.
    Normally you should have as many lives as you want.
    If you got a 'SEARCH FAILED' then ... it failed, see below for help.
    Using this method, the value is only changed once, but if you press F3
    then enter the offset and the value, it will be changed to the specified
    value 60 times per sec., so it looks like it is frozen. Pressing F3 then
    the address will unfreeze the value.
    Now, you can research value using a relative method. that's to say that
    instead of searching exact values, you can simply tell hu-go! to search
    for variation of the variable. e.g. each time you lose a life, you can
    make a research on -1, i.e. the variable you're looking for have been
    decreased by 1. With this method, you don't have to worry about the base
    value used to represent the variable (see hints concerning this).
    When you want to make a relative research, you have to use F1 as
    previously but instead of typing the plain number, you must prefix it
    with '+' or '-'. For the first research, you don't have to worry about
    the value you're giving, it's simply used to initialize the temporary
    file containing all the possible variables with all the current values.
    Once done, you can press F1 then '+1' or '-3' and such. From a technical
    point of view, it's possible to mix normal and relative research but if
    you do absolute research, there's no point on doing relative one.

--[ CHEATING HINTS ]---------------------------------------------------------

     -- Be careful, you may think the cheat didn't work, in fact, some
     variables aren't updated each frame so try to lose a life or if you
     modified money try to buy something... then you may see the difference.
     -- You aren't obliged to search for altered values, you can make a
     search for 2 lifes then 5 sec. later you search for 2 lifes again,...
     I suggest you search for the same value twice very quickly. If you look
     twice for the same value with only a half a sec. interval, you will
     certainly eliminate a good amount of 'bad' variables.
     -- Once a search is complete and you no longer get a lot values each
     time you search, you may stay stuck because two variables have the same
     value at the same moment (often for core and screen purposes). If that
     is the case go and check the file named ROM.FP0 (where ROM is the name
     of the rom), this contains the different possible offsets. It's up to
     you.
     -- Sessions of research are kept between two launches of the emulator.
     -- If you want to start a new session, just make a 'SEARCH FAILED'
     (Search for 25 then 6 then 79 in a very reduced interval, if you can't
     get an 'SEARCH FAILED' then you will be the next on my guinea pig list
     for trying the direct synaptic link ;).
     -- Sometimes, the value on screen isn't stored like shown, e.g. if you
     have 5 lives, maybe the variable 'LIFE' is set at 4 or 6, try to search
     for 'value'+1 or 'value'-1, it may work... (like the number of balls in
     Devil Cr*sh).
     The best to avoid this kind of problem is using relative value research.
     -- The search only works on bytes but a variable may take 2, 3 or more
     bytes. In this case try modifying the byte just 1 byte above or below
     the one you found (e.g. if you've found that putting a value at address
     X would change the money a bit, putting a value at address X+1 will
     certainly change the money a lot).

--[ DEVELOPERS CORNER ]------------------------------------------------------

	Hu-Go! now exposes a large part of the current game internal variables via
	shared memory (only linux/freebsd for now, soon windows too).
	You can use the shared memory of identifier 25679. It contains a structure
	of type struct_hard_pce as defined in shared_memory.h (you should grab the
	source archive of course). You can then alter or read all the quite self
	explanatory variables out there. As for controlling the cpu, you can use
	the s_external_control_cpu field.
	  -1 => Full speed
	  0  => Emulation paused
	 >0  => Number of opcodes to run before pausing
	You have to recompile Hu-Go! using --enable-shared-memory to benefit this
	feature.

--[ THANKS ]-----------------------------------------------------------------

   Special thanks :
 *> -- Bacon boy 99 (Ex-Planet Rom webmaster, the former logo,    <*
       having sent me some Cds and in fact, lots of things)
	-- Ixion for the lots of bugs/improvements he worked on recently
	-- Blake- for the bugs he fixed while doing his pce emu on gp32
    -- ]pit[ for all his help (among all the new logo and banners)
    -- Nyef for all the infos he gave me on CD emulation
    -- Lester Barrows for his help on the linux code (notably, pad support from
              his work)
	-- Bt Garner (ideas, lots of stuff including hosting my site now, ...)
    -- Ishan (ex Vlendr'it) for the mailing list, tweak mode tests, finding
       nice code resources on the web and scanline mode
    -- TOZTWO for the nice HTML doc
    -- Tormod Tjaberg for the MP3 length detection code
    -- fixo, cools, sALTY, codemaster, Raoh, MrF, dus, Yuu and all the #emu
       dudes on IrcNet ;)
    -- ElmerYud coz' he's Hu-Go! publicity manager ^_^
    -- tAGGY for two nice pictures
    -- SirJaguar, Nico, Ded, ZePoulpe, Leto_II, Ziller, Readiosys and guys on
       #utopiasoft or #nec4ever
    -- Dirk Steven (EAGLE is really very nice)
    -- Dave Shadoff (TGSIM and TGSIMGPP, longs mails and lots of ideas,
       author of the little rom included, very nice guy)
    -- Marat Fayzullin (BASE SOURCE for 6502)
    -- Bero (Additional SOURCE)
    -- Hmmx (More additional SOURCE)
    -- DJ Delorie (DJGPP, what a great thing!)
    -- Shawn Hargreaves (ALLEGRO is great)
    -- David Michel (MAGIC ENGINE is still the best emu!!!, futhermore he's
       very friendly and fair-play. Also the Author of the Magic Kit which
       allow you to create your own PC Engine games)
    -- The info-zip group for making unzipping easy (sometimes ^_^)

    -- Zophar domain (www.zophar.net)
    -- Jens Christian Restemeier (DOCS)
    -- Joe LoCicero (DOCS)
    -- David Woodford (DOCS)
    -- Videoman (DOCS)
    -- Charles W Sandmann (CWSDPMI, this program is under GPL license and you
       can get the source at http://www.delorie.com/djgpp/ )
    -- Markus F.X.J. Oberhumer & Laszlo Molnar (contribution to UPX, an
       excellent EXE-packer used in this release)

    Diverse thanks:
    -- Bouli (www.multimania.com/booemu/
              arcades.le-village.com/megrom/)
       for using Hu-Go! for his screenshots ;)
    -- Michael Sheldows (www.homestead.com/sheldows)
       for trying to port Hu-Go! to a new OS of his own
    -- Mr Iceberg (www.multimania.com/pceaudit)
       for offering a PCE ROM manager based on FPCEID

    Others I may have forgotten (Sorry!!!)
    (send me a mail if you consider you should be credited...)

    If you have any questions, suggestions, propositions for help or
    mirroring, bug reporting, or non working games, don't hesitate,
    send a e-mail (I love e-mails) to : ZEOGRAD@ZEOGRAD.COM

    (You can also send money, car keys, credit card with PIN number,
    video games, girlfriends, ask for snail mail address !! ;)

      .  ___   ____                _________           ___
       .|  `|_|   `| ___ ___  __ .|    ____/ _______ .|  `|
     .:|     _     ||  `|  `|(__)|    (_  `|/   _  `\|____/:.
...:::||____|:|____||_______/::::\_________/\_______/(____)::::...
      `-*-- -  -   -    -      -            -              ^cls

