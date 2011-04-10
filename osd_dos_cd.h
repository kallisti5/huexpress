#ifndef _INCLUDE_OSD_H
#define _INCLUDE_OSD_H

/*
 * Generic include part
 */
#include <go32.h>
#include <dpmi.h>
#include <sys\farptr.h>
#include "cleantyp.h"

/*
 * Mscdex include part
 */
#include <string.h>
#include <sys\segments.h>

/*
 * Aspi include part
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "aspi.h"
#include "aspi_int.h"
#include "scsidefs.h"

typedef enum {
        mscdex_driver,
        aspi_driver } osd_cd_driver_type;

extern osd_cd_driver_type osd_cd_driver;

#endif
