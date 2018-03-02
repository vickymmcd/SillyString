#include <ncurses.h>
#include <string.h>

int main()
{
  char msg[]="What is your name? ";
  char ques[] = "Would you like to escape? (yes or no) ";
  char escape[] = "Congrats! You escaped!";
  char no_escape[] = "Sorry, you did not escape.";
  char name[80];
  char resp[80];
  int row, col;

  initscr();
  getmaxyx(stdscr, row, col);
  mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);

  getstr(name);
  clear();
  mvprintw(row/2, (col-(strlen(name)+6))/2, "Hello %s", name);

  getch();

  clear();
  mvprintw(row/2, (col-strlen(ques))/2, "%s", ques);

  getstr(resp);
  clear();
  if(strcmp(resp, "yes") == 0){
    mvprintw(row/2, (col-strlen(escape))/2, "%s", escape);
  }
  else{
    mvprintw(row/2, (col-strlen(no_escape))/2, "%s", no_escape);
  }

  getch();
  endwin();

  return 0;

}
