#ifndef __MAIN_H
#define __MAIN_H


#include "video.h"

void cleanExit(int exitCode);
void drawDesc();
void drawBuffer (struct vidBuf* buffer);
void moveVert (int n, int max);
struct vidBuf buffer;
void drawLineSingle (struct vidBuf* buffer, int itemIndex);
void openVideo (char* id);
void intArgs (int argc, char* argv[]);


#endif
