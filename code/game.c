#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <string.h>
#include "questions.h"


/* Sets up gameplay for NCURSES escape the room game
 */
int main(int argc, char *argv[])
{
    // setup NCURSES
    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do new line carriage return */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) echo();         /* echo input */


    // set up variables for question 1
    int num = 0;
    char *question1 = "You find yourself locked out of the room. You need to acquire a key, "
    "but where should you look? The forgetful librarians always leave hints for themselves "
    "in case they ever lock themselves out. In this case, the hint is: ELBAT EHT REDNU\n";

    int num_choices = 4;
    char *options1[num_choices];
    options1[0] = "Inside the cupboard";
    options1[1] = "Under the table";
    options1[2] = "Under the door mat";
    options1[3] = "On top of the shelf";

    char question2[] = "Would you like to escape? (yes or no) ";

    mc_question(question1, num_choices, options1, 1);
    fr_question(question2, "yes");

    // wait for the user to press a key after the question
    getch();

    // exit NCURSES
    endwin();
    exit(0);
}
