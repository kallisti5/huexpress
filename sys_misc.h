#ifndef _INCLUDE_SYS_MISC_H
#define _INCLUDE_SYS_MISC_H

/*
 * Miscellaneous section
 *
 * Here are function that don't belong to a set of function. It doesn't mean
 * they shouldn't be implemented but rather that they are important enough
 * to have their own section :)
 */

  /*
   * osd_init_machine
   *
   * This function is called once at the very beginning of the emulation and
   * must set once for all certain variables.
   * e.g. it should allocate mem for the osd_gfx_buffer variable, init joypad
   * stuff e.g. or anything else that will last the whole emulation session.
   * return 0 on success else non zero value
   */
   int osd_init_machine(void);

  /*
   * osd_shut_machine
   *
   * This is called once at the end of the emulation should be used to free
   * resources allocated in osd_init_machine
   */
   void osd_shut_machine(void);

  /*
   * osd_keypressed
   *
   * Behaves like kbhit, returning 0 is case no key have been pressed and a
   * non zero value if there's any key that can be read from osd_readkey
   */
   SChar osd_keypressed(void);

  /*
   * osd_readkey
   *
   * Return info concerning the first keystroke, lower byte is the ascii code
   * while the higher byte contains the scancode of the key.
   * Once called, discard the value in the keystroke buffer
   */
   UInt16 osd_readkey(void);

  /*
   * osd_fix_filename_slashes
   *
   * Update a string in parameter, converting the "wrong slashes" into slashes
   * expected by the current os
   */
	void osd_fix_filename_slashes(char* s);
	
	/*
	 * osd_init_paths
	 *
	 * Set global path and filename variables :
	 *  - short_exe_name
	 *  - log_filename
	 *  - sav_basepath
	 *	- tmp_basepath
	 *  - video_path
	 */
	void osd_init_paths();
	
	/*
	 * gamepad_driver
	 *
	 * When needed, represents the type of the joypad(s) to expect
	 */
	extern int gamepad_driver;

  /*
	 * synchro
	 *
	 * On ports where speed isn't auto regulated, tell whether we need to manually
	 * reduce the speed or not
	 */
  extern char synchro;
	
#endif
