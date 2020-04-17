#include "ui.h"
#include "main.h"
#include "video.h"
#include "../gotoc.h"

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>


WINDOW *scrn;

char keyUp = 'k',
     keyDown = 'j',
     keySearch = 'o',
     keyDesc = 'd',
     keyEnt = 'l';

int cursorIndex = 0,
    padx = 3, pady = 1;


bool pop = false;

char* nextPage;
char* formatString;
char* searchString;
char* defaultFormatString = "$BROWSER %s";
char* linkString = "https://www.youtube.com/watch?v=%s";


void cleanExit(int exitCode);
void drawDesc();
int main (int argc, char *argv[]) {


	intArgs (argc, argv);
	__init__ ();

	if (pop || !searchString ) { nextPage =  videoMostPopularC (); fillInfo (&buffer); }
	else { nextPage = videoSearchC (searchString); fillInfo (&buffer);}
	if (!formatString) { formatString = defaultFormatString; }



	wchar_t d;


	scrn = initscr();
	endwin();

	cbreak();

	clear();
	refresh();
	curs_set(0);

	drawBuffer (&buffer);


	while(1) {

		d = getch();

		if (d == keyDown) { moveVert (1, buffer.size); }

		else if (d == KEY_RESIZE) { drawBuffer (&buffer); }

		else if (d == keyUp) { moveVert (-1, buffer.size); }

		else if (d == keyEnt) { openVideo (buffer.id[cursorIndex]); }

		else if (d == keyDesc) { drawDesc(); }

		move (-1, 0);
		drawLine (0, NULL);
		if (strlen (nextPage) != 6) { drawPrompt (nextPage); }
	}


	return 0;
}

void drawDesc()
{
	drawPrompt("");
}

//Inteprets the arguments
void intArgs (int len, char* argList[]) {
	char c;
	while ((c = getopt (len, argList, "hpdl:i:o:")) != -1)
		switch (c)
			{
			case 'h':
				system("cat /etc/yttui/help");
				exit(1);
				break;
			case 'l':
				setLangC (optarg);
				break;
			case 'p':
				pop = true;
				break;
			case 'i':
				searchString = optarg;
				break;
			case 'o':
				formatString = optarg;
			case 'd':
				linkString = "%s";
				break;
			default:
				abort ();
		}

}



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

void openVideo (char* id) {

	char runStr[300];
	char linkStr[100];

	sprintf (linkStr, linkString, id);
	sprintf (runStr, formatString, linkStr);
	system(runStr);
	drawBuffer(&buffer);

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
		// Fix double line
		if (count == cursorIndex) { attroff (A_STANDOUT); }

		++count;
	}
	if (buffer->size == 0) { drawPrompt ("No results."); getch(); cleanExit(-1); }
	move (-1, 0);
}


void cleanExit(int exitCode)
{
	exit(exitCode);
	clear();
	endwin();
}
