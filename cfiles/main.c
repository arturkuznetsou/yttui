#include "nav.h"
#include "ui.h"
#include "main.h"
#include "video.h"
#include "../gotoc.h"

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>



WINDOW *scrn;

char keyUp = 'k',
     keyDown = 'j',
     keySearch = 'o',
     keyDesc = 'd',
     keyEnt = 'l',
     keyNextPage = 'L',
     keyPrevPage = 'H';

int cursorIndex = 0,
    padx = 3, pady = 1;


bool pop = false;

char* nextPage;
char* prevPage;
char* formatString;
char* searchString;
char* defaultFormatString = "$BROWSER %s";
char* linkString = "https://www.youtube.com/watch?v=%s";

struct vidBuf buffer;


int main (int argc, char *argv[]) {


	intArgs (argc, argv);



	char d;


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

		else if (d == 27) { cleanExit(1); }

		else if (d == keyNextPage){
			page(1);
		}
		else if (d == keyPrevPage){
			page(-1);
		}

		move (-1, 0);
		drawLine (0, NULL);
	}


	return 0;
}

void drawDesc()
{
	drawPrompt("");
}

//Interprets the arguments
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
	if (buffer.size == 0) { printf ("No results.\n"); cleanExit(-1); }
}



void cleanExit(int exitCode)
{
	clearBuffer(&buffer);
	clear();
	endwin();
	exit(exitCode);
}
