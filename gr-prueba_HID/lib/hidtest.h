
#ifndef HIDTEST_H__
#define HIDTEST_H__

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"
 
// Headers needed for sleeping.
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// include libraries
void main_hidtest(void);

#endif
