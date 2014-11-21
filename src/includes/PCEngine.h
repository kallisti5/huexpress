#ifndef _PCENGINE_H
#define _PCENGINE_H

extern "C" {
#include "debug.h"
#include "pce.h"
#include "iniconfig.h"
}


class PCEngine {

public:
						PCEngine();
						~PCEngine();

	int					LoadFile(char* file);
	void				Run();

	int					isReady() { return fReady; };

private:

	int					fReady;

	//! name of the backup ram filename
	char				fBackupMem[PATH_MAX];

	struct host_machine	fHost;
	struct hugo_options	fOptions;
};


#endif
