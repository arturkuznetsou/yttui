#include "nav.h"
#include "ui.h"
#include "main.h"
#include "video.h"
#include "../gotoc.h"

#include "../config.h"
#include <locale.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>



WINDOW *scrn;

int cursorIndex = 0;
char* nextPage;
char* prevPage;
char* formatString;
char* defaultFormatString = "setsid -f $BROWSER %s > /dev/null";
char* linkString = "https://www.youtube.com/watch?v=%s";

struct vidBuf buffer;


int main (int argc, char *argv[]) {

	setlocale(LC_ALL, "");
	intArgs (argc, argv);
	scrn = initscr();
	endwin();
	cbreak();
	clear();
	refresh();
	curs_set(0);

	drawBuffer (&buffer);


	wchar_t d;
	while(1) {

		d = getch();

		switch(d) {
			case keyDown:
				moveVert (1, buffer.size);
				break;
			case KEY_RESIZE :
				drawBuffer (&buffer);
				break;
			case keyUp :
				moveVert (-1, buffer.size);
				break;
			case keyEnt :
				openVideo ();
				break;
			case escKey :
				cleanExit(1);
				break;
			case keyNextPage:
				page(1);
				break;
			case keyPrevPage:
				page(-1);
				break;
			case keyUpByTen:
				moveVert(10, buffer.size);
				break;
			case keyDownByTen:
				moveVert(-10, buffer.size);
				break;
		}

		move (LINES + 1, 0);
	}


	return 0;
}


//Interprets the arguments and sets up some other things
void intArgs (int len, char* argList[]) {
	setKeyC(devKey);
	char c;
	while ((c = getopt (len, argList, "hdl:o:")) != -1)
		switch (c) {
			case 'h':
				system("cat /usr/local/etc/yttuihelp");
				exit(1);
				break;
			case 'l':
				setLangC (optarg);
				break;
			case 'o':
				formatString = optarg;
				break;
			case 'd':
				linkString = "%s";
				break;
			default:
				abort ();
				break;
		}
	__init__ ();
	int size = 0;
	for(int i = optind; i < len; i++)
	{
		size += 1;
		size += strlen(argList[i]);
	}
	char string[size + 1];
	string[0] = '\0';
	for(int i = optind; i < len; i++)
	{
		strcat(string, argList[i]);
		strcat(string, " ");
	}
	if(!size){
		nextPage =  videoMostPopularC ();
	}
	else {
		nextPage = videoSearchC (string);
	}
	fillInfo (&buffer);
	if (!formatString) { formatString = defaultFormatString; }
	if (buffer.size == 0) { printf ("\nNo results.\n"); cleanExit(-1); }
}


void cleanExit(int exitCode)
{
	clearBuffer(&buffer);
	clear();
	endwin();
	exit(exitCode);
}
