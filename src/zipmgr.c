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

	zip_int64_t numberOfFiles = zip_get_num_entries(zipHandle,
		ZIP_FL_UNCHANGED);

	zip_int64_t position;
	for (position = 0; position < numberOfFiles; position++) {
		const char* filename = zip_get_name(zipHandle, position, 0);
		if (strcasestr(filename, ".PCE")) {
			MESSAGE_INFO("Found a valid rom within zip file: %s\n",
				filename);
			strncpy(foundGameFile, filename, PATH_MAX);
			zip_close(zipHandle);
			return ZIP_HAS_PCE;
		}
		if (strcasestr(filename, ".HCD")) {
			MESSAGE_INFO("Found a valid cd game definition within zip file: "
				"%s\n", filename);
			strncpy(foundGameFile, filename, PATH_MAX);
			zip_close(zipHandle);
			return ZIP_HAS_HCD;
		}
		if (strcasestr(filename, ".ISO")) {
			MESSAGE_INFO("Found an ISO within the zip file: %s\n",
				filename);
			strncpy(foundGameFile, filename, PATH_MAX);
			zip_close(zipHandle);
			return ZIP_HAS_ISO;
		}
	}
	
	zip_close(zipHandle);
	return ZIP_HAS_NONE;
}
