#include <curses.h>


// Definition of keys
#define keyUp 'k'
#define keyDown 'j'
#define keySearch 'o'
#define keyDesc 'd'
#define keyEnt 'l'
#define keyNextPage 'L'
#define keyPrevPage 'H'

// Number 4 = CTRL + u
#define keyUpByTen 4
// Number 21 = CTRL + u
#define keyDownByTen 21
// Number 27 = ESC key
#define escKey 27
char* devKey = "AIzaSyChxouOhmPo_6GSs-21XYnTxyJZ5YHPJAU";

/*
 * Margin to the left and top of the screen
 */
int padx = 2, pady = 0;
