#ifndef __MAIN_H
#define __MAIN_H


#include "video.h"


char* formatString;
char* defaultFormatString;
char* linkString;

int cursorIndex;
int pady;
int padx;
void cleanExit(int exitCode);
void drawDesc();
void moveVert (int n, int max);
struct vidBuf buffer;
void openVideo ();
void intArgs (int argc, char* argv[]);


#endif
