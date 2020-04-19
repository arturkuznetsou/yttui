#include "../gotoc.h"
#include "main.h"
#include "video.h"
#include <string.h>
#include <curses.h>


int drawLine (int line, ...) {
	//draw empty line to clear the line at the index
	//draw empty line to clear the line at the index
	for (int n = 0; n < COLS; n++) { mvaddch (line, n, ' ');}
	//draw empty line to clear the line at the index
	//draw empty line to clear the line at the index

	int count = 0;

	va_list args;
	va_start (args, line);
	char* string;

	while (1) {
		if (count % 2 == 0){
			if( (string = va_arg (args, char*)) == NULL) { break; }
		}
		else{

			int i = va_arg (args, int);
			int len = strlen(string);
			int rest = len + i - COLS;

			if (i < COLS) {
				if (rest <= 0) {
					mvaddstr (line, i, string);
				}
				else {
					char newStr[len - rest + 1];
					memcpy (newStr, string, len - rest);
					newStr[len - rest] = '\0';
					mvaddstr (line, i, newStr);
				}
			}
		}
		count += 1;
	}
	va_end (args);
	move (0, 0);
	return line + 1;
}

int drawPrompt (char* string){

	attron (A_STANDOUT);
	drawLine ((int)(LINES/2 - 2), NULL);
	drawLine ((int)(LINES/2 + 2), NULL);
	attroff (A_STANDOUT);
	drawLine ((int)(LINES/2 + 1), NULL);
	drawLine ((int)(LINES/2 - 1), NULL);

	drawLine ((int)(LINES/2), NULL);
	mvaddstr ((int)(LINES/2), (int)(COLS/2), string);

	refresh();
	move (-1, 0);
}

void drawLineSingle (struct vidBuf* buffer, int itemIndex) {
		char viewString[40];
		char likeString[40];
		char dislikeString[40];
		char dateString[11];

		strncpy (dateString, buffer->date[itemIndex], 10);
		dateString[10] = '\0';

		sprintf (viewString, " ( o) %d", buffer->views[itemIndex]);
		sprintf (likeString, ":) %d", buffer->likes[itemIndex]);
		sprintf (dislikeString, ":( %d", buffer->dislikes[itemIndex]);


		drawLine (
				itemIndex + pady,


				viewString, 145,
				likeString, 165,


				dislikeString, 180,
				dateString, 195,


				buffer->title[itemIndex], padx,
				buffer->channelName[itemIndex], padx +100,
				NULL);
		mvaddch(itemIndex + pady, 143, ACS_VLINE);
}
void drawBuffer (struct vidBuf* buffer) {
	clear();
	int count = 0;
	while (count < buffer->size && count < LINES - pady) {
		if (count == cursorIndex) { attron (A_STANDOUT); }
		drawLineSingle (buffer, count);
		if (count == cursorIndex) { attroff (A_STANDOUT); }
		++count;
	}
	move (-1, 0);
}





