#ifndef __MAIN__H
#define __MAIN_H


#include "video.h"

void drawBuffer (struct vidBuf* buffer);
void moveVert (int n, int max);
struct vidBuf buffer;
void drawLineSingle (struct vidBuf* buffer, int itemIndex);
void openVideo (char* id);
void intArgs (int argc, char* argv[]);


#endif
