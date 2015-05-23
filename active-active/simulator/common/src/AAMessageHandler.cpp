#include <QtGlobal>
#include "AAMessageHandler.h"
#include "CommandLineArguments.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>

void AAMessageHandler(QtMsgType type, const char* msg)
{
    if (type == QtFatalMsg){
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }

    bool isQuietArgumentSet = CommandLineArguments::isKeySet(CL_QUIET_OPTION);
    if (isQuietArgumentSet)
        return;

	bool isVerboseArgumentSet = CommandLineArguments::isKeySet(CL_VERBOSE_OPTION); 
	if ( type == QtDebugMsg && !isVerboseArgumentSet)
		return;

    fprintf(stderr, "%s\n", msg);


}
