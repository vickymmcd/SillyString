#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <string.h>
#include "questions.h"


/* Prints a losing message when the player loses and exits the game
 */
void lose(){
  clear();
  printw("Sorry, that is not right, you did not escape the room today");
  refresh();
  // wait for a user to press a key after the message is displayed
  getch();
  // exit NCURSES
  endwin();
  exit(0);
}

/* Prints a winning message when the player wins and exits the game
 */
void win(){
  clear();
  printw("Congratulations! You escaped!");
  refresh();
  // wait for a user to press a key after the message is displayed
  getch();
  // exit NCURSES
  endwin();
  exit(0);
}

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

    int result; // variable to store correct/incorrect

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

    // set up variables for questions 2 and 3
    char *question2 = "You look under the table and see a green plus sign, a yellow minus "
    "sign, and a red plus sign. You also see the letters \"mpqem\" scrawled underneath the "
    "table. You suspect it is a word coded using a cipher. What is the word? (Type your "
    "answer in all lowercase.)";

    char *question3 = "You walk over to the door and notice a drawing on the center of the "
    "door. It includes 5 yellow circles, 6 red circles, and 3 green circles. You suspect "
    "it means something but are not quite sure what. Click on the center of the screen (to "
    "simulate knocking on the door). Press \"e\" to submit that you are done knocking.";

    result = mc_question(question1, num_choices, options1, 1);
    if(result==1){
      lose();
    }
    result = fr_question(question2, "knock");
    if(result==1){
      lose();
    }
    result = mouse_question(question3, 4);
    if(result==1){
      lose();
    }
    else if(result==0){
      win();
    }
}
