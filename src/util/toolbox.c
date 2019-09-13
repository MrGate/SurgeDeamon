#include <stdio.h>

#include "util/toolbox.h"

void dumpArgs(int argc, char *argv[])
{
    printf("\nARG Dumper ==========================\n");
    printf("ARGC : %d\n", argc);
    for(int x = 0; x < argc; x++)
    {
        printf("ARGV[%d] : %s\n", x, argv[x]);
    }
    printf("=====================================\n");
}

void cSpinLock()
{
	// Code 
	// this might be system dep
}

void cSpinUnlock()
{
	// Code
}
