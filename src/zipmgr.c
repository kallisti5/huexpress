/*
 * Copyright 2013, Alexander von Gluck, All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *              Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include "zipmgr.h"

#include <zip.h>

#include "debug.h"


uint32
zipmgr_probe_file(char* zipFilename, char* foundGameFile)
{
	struct zip* zipHandle = zip_open(zipFilename, 0, NULL);
	if (zipHandle == NULL) {
		MESSAGE_ERROR("Zip %s error: %s\n", zipFilename,
			zip_strerror(zipHandle));
		return ZIP_ERROR;
	}

	zip_int64_t locatedIndex = -1;
	
	locatedIndex = zip_name_locate(zipHandle, ".pce", ZIP_FL_NOCASE | ZIP_FL_NODIR);

	if (locatedIndex != -1)
		MESSAGE_INFO("Match!\n");
	else
		MESSAGE_INFO("No-Match!\n");

	zip_close(zipHandle);
	return ZIP_HAS_NONE;
}
