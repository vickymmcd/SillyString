#include <ncurses.h>
#include <string.h>


int main()
{
	MEVENT event;

	/* Initialize curses */
	initscr();
	clear();
	noecho();
	cbreak();	//Line buffering disabled. pass on everything

  int ch;

	/* Get all the mouse events */
	mousemask(BUTTON1_CLICKED, NULL);

  ch = getch();
    if(ch == KEY_MOUSE){
        if(getmouse(&event) == OK){
          if(event.bstate & BUTTON1_CLICKED){
            printw("hello friend");
          }
        }
      }
      refresh();
      getch();
	endwin();
	return 0;
}
