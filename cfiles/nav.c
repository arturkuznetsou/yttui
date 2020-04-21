#include "nav.h"
#include "main.h"
#include "video.h"
#include "ui.h"

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int pageIndex = 0;
struct vidBuf* cache;

void moveVert (int n, int max) {

	drawLineSingle (&buffer, cursorIndex);
	if (cursorIndex + n >= max) {
		cursorIndex = max - 1;

	}
	else if (cursorIndex + n < 0){
		cursorIndex = 0;

	}
	else{
		cursorIndex += n;
	}
	attron (A_STANDOUT);
	drawLineSingle (&buffer, cursorIndex);
	attroff (A_STANDOUT);

}

void openVideo () {

	char* id = buffer.id[cursorIndex];
	char runStr[300];
	char linkStr[100];

	sprintf (linkStr, linkString, id);
	sprintf (runStr, formatString, linkStr);
	system(runStr);
	drawBuffer(&buffer);

}

void page(int move)
{
	cache = realloc(cache, sizeof(struct vidBuf) * (pageIndex + 1));
	cache[pageIndex] = buffer;
	pageIndex += 1;
	clearBuffGo();
	nextPage = videoPageIdC(nextPage);
	fillInfo (&buffer);
	drawBuffer (&buffer);
}
