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
int len = 1;
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

/*
1 to move right
-1 to move left
Right now you cant skip more than one page. This would bug this thing out.
*/
void page(int move)
{
	pageIndex += move;
	//Sets the pageIndex to 0 if its less than 0
	pageIndex = pageIndex - (pageIndex * (pageIndex < 0));
	if(pageIndex >= len)
	{
		cache = realloc(cache, sizeof(struct vidBuf) * len);
		cache[len - 1] = buffer;
		len += 1;
		drawPrompt("Retrieving next page.....");
		clearBuffGo();
		nextPage = videoPageIdC(nextPage);
		fillInfo (&buffer);
	}
	else{
		buffer = cache[pageIndex];
	}
	if(buffer.size == 0)
	{
			drawPrompt("No results");
	}
	else{
			drawBuffer (&buffer);
	}
}
