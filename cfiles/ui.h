#ifndef YT_TUI_H
#define YT_TUI_H
#include "video.h"

extern int pady;
extern int padx;
extern int cursorIndex;
void drawLineSingle (struct vidBuf* buffer, int itemIndex);
void drawPrompt (char* string);
int drawLine (int line, ...);
void drawBuffer (struct vidBuf* buffer);
#endif
