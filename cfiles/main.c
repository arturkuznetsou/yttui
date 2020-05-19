#include "nav.h"
#include "ui.h"
#include "main.h"
#include "video.h"
#include "../gotoc.h"

#include "config.h"
#include <locale.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>



WINDOW *scrn;

int cursorIndex = 0,
    padx, pady;


bool pop = false;

char* nextPage;
char* prevPage;
char* formatString;
char* searchString;
char* defaultFormatString = "firefox %s & disown";
char* linkString = "https://www.youtube.com/watch?v=%s";

struct vidBuf buffer;


int main (int argc, char *argv[]) {


	setlocale(LC_ALL, "");
	intArgs (argc, argv);



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

		else if (d == keyEnt) { openVideo (); }

		else if (d == escKey) { cleanExit(1); }

		else if (d == keyNextPage){
			page(1);
		}
		else if (d == keyPrevPage){
			page(-1);
		}
		else if (d == keyUpByTen){
			moveVert(10, buffer.size);
		}
		else if (d == keyDownByTen){
			moveVert(-10, buffer.size);
		}

		move (-1, 0);
		drawLine (0, NULL);
	}


	return 0;
}


//Interprets the arguments and sets up some other things
void intArgs (int len, char* argList[]) {
	setKeyC(devKey);
	char c;
	while ((c = getopt (len, argList, "hpdl:i:o:")) != -1)
		switch (c)
			{
			case 'h':
				system("cat /usr/local/etc/yttuihelp");
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
				break;
			case 'd':
				linkString = "%s";
				break;
			default:
				abort ();
		}
	__init__ ();

	if (pop || !searchString ) {
		nextPage =  videoMostPopularC ();
		fillInfo (&buffer);
	}
	else { nextPage = videoSearchC (searchString); fillInfo (&buffer);}
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
