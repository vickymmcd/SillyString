#include <ncurses.h>			/* ncurses.h includes stdio.h */
#include <string.h>
#include <stdlib.h>

int main()
{
 char title[] ="Silly String Input Example\n\n";
 char mesg[]="What is your name?\n";		/* message to be appeared on the screen */
 char mesg1[]="My name is: ";
 char name[80];
 char choice[5];
 int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */
 initscr();				/* start the curses mode */
 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 mvprintw(1,(col-strlen(title))/2,"%s",title);
                     		/* print the message at the center of the screen */
 printw("%s",mesg);
 printw("%s",mesg1);

 getstr(name);
 printw("Hello, %s. It's nice to meet you.\n\n", name);

 printw("Pick 1 or 2.\nI choose: ");
 getstr(choice);

 switch(atoi(choice)) {
     case 1:
         printw("You chose 1! Congrats you won!\n");
         break;
     case 2:
         printw("You chose 2. Sad. You lost.\n");
         break;
     default:
         printw("I don't know what you chose, but you win anyway.\n");
         break;
 }
 getch();
 endwin();

 return 0;
}
