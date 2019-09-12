#pragma once

#include <stdio.h>


void dumpArgs(int argc, char *argv[]);

// Minimal Spinlock Functions
void cSpinLock();
void cSpinUnlock();