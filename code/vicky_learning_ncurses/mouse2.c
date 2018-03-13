#include <ncurses.h>
#include <assert.h>

int main() {
  int ch, count=0;
  int row, col;
  MEVENT event;

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  clear();
  cbreak();

  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  // get the dimensions of the screen
  getmaxyx(stdscr, row, col);
  int xtolerance = 10;
  int ytolerance = 5;

  while ((ch = getch()) != 'q')
  {
    count++;
    //mvprintw(1, 1, "Has mouse: %d", has_mouse());
    //mvprintw(2, 1, "Key code: %x; mouse code:%x", ch, KEY_MOUSE);
    if (ch == KEY_MOUSE)
    {
      clear();
      assert(getmouse(&event) == OK);
      mvprintw(3, 3, "Mouse Event: x=%d, y=%d z=%d",
               event.x, event.y, event.z);
      mvprintw(4, 3, "row: %d col: %d", row, col);
      mvprintw(5, 3, "Mouse button mask: %x", event.bstate);
      if(event.bstate & BUTTON1_CLICKED){
        if(event.y >= (row/2)-ytolerance && event.y <= (row/2)+ytolerance){
          if(event.x >= (col/2)-xtolerance && event.x <= (col/2)+xtolerance){
            mvprintw(2, 1, "hit in center!");
          }
        }
        mvprintw(1, 1, "left button click");
      }
    }
    mvprintw(6, 1, "Event number: %4d",count);
    refresh();
  }
  endwin();
}
