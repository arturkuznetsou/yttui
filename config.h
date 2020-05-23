#include <curses.h>
char keyUp = 'k',
     keyDown = 'j',
     keySearch = 'o',
     keyDesc = 'd',
     keyEnt = 'l',
     keyNextPage = 'L',
     keyPrevPage = 'H',
     // Number 4 = CTRL + u
     keyUpByTen = 4,
     // Number 21 = CTRL + u
     keyDownByTen = 21,
     // Number 27 = ESC key
     escKey = 27;
char* devKey = "AIzaSyChxouOhmPo_6GSs-21XYnTxyJZ5YHPJAU";

/*
 * Margin to the left and top of the screen
 *
 */
int padx = 2, pady = 1;
