#include <stdlib.h>
#include <curses.h>
#include <menu.h>
#include <string.h>
#include <assert.h>
#include "questions.h"


/* Sets up an NCURSES multiple choice question
 *
 * question: text of the question as a string
 * n_choices: number of choices
 * options: array of strings which are the choices
 * correct: index of correct choice in options
 */
int mc_question(char *question, int n_choices, char *options[], int correct){

  // set up variables for this functions
  char letter[n_choices][2];
  const char *response;
  ITEM **my_items;
  WINDOW *my_menu_win;
  int i;
  int c;
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

  clear();

  // only allow for 7 or fewer multiple choice options
  if(n_choices > 8){
    printw("Sorry, this only supports questions with 7 or fewer choices");
    return -1;
    //endwin();
    //exit(0);
  }

  printw(question);

  // set up the menu items with the appropriate letter and option text
  for(i=0; i<n_choices; i++){
    // A is 65 in ASCII
    letter[i][0] = (char)i+65;
    letter[i][1] = '\0';
    my_items[i] = new_item(letter[i], options[i]);
  }

  // set up the menu with the items
  MENU *my_menu = new_menu(my_items);

  // sets up a menu window (height, width, y, x)
  my_menu_win = newwin(15, 60, 6, 8);
  // activates the keypad for that window
  keypad(my_menu_win, TRUE);

  // put the menu into the menu window
  set_menu_win(my_menu, my_menu_win);
  // sets up subwindow for menu so it is nicely padded in center
  set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
  // sets max display size for menu and makes scrollable if necessary
  set_menu_format(my_menu, 5, 1);

  set_menu_mark(my_menu, " * ");

  // draws a box around the menu window
  box(my_menu_win, 0, 0);
  refresh();

  // post the menu and refresh everything
  post_menu(my_menu);
  wrefresh(my_menu_win);
  refresh();

  // handle selection and scrolling through the menu
  while((c = getch()) != '\r')
  {   switch(c)
      { case KEY_DOWN:
          menu_driver(my_menu, REQ_DOWN_ITEM);
          break;
        case KEY_UP:
          menu_driver(my_menu, REQ_UP_ITEM);
          break;
      }
      wrefresh(my_menu_win);
  }

  // display the user's choice
  clear();
  printw("You chose choice: %.1s\n", item_name(current_item(my_menu)));
  printw("Which is: %s\n", item_description(current_item(my_menu)));

  // get response then free items
  response = item_name(current_item(my_menu));
  free_item(my_items[0]);
  free_item(my_items[1]);
  free_item(my_items[2]);
  free_item(my_items[3]);
  free_menu(my_menu);
  delwin(my_menu_win);

  // determine if they were right or wrong return 0 for correct and 1 for incorrect
  if(strcmp(response, letter[correct])==0){
    return 0;
  }
  else{
    return 1;
  }

}

/* Sets up an NCURSES free response question
 *
 * question: text of the question as a string
 * answer: string that represents correct input
 */
int fr_question(char *question, char *answer){
  char resp[7];

  // print the question
  clear();
  mvprintw(0, 0, "%s", question);
  mvprintw(6, 6, "");

  // get the input response and determine if right (return 0) or wrong (return 1)
  getnstr(resp, 6);
  clear();
  if(strcmp(resp, answer) == 0){
    return 0;
  }
  else{
    return 1;
  }
}

/* Sets up an NCURSES mouse question
 *
 * question: text of the question as a string
 * num_knocks: number of times they should click the center of the screen
 */
int mouse_question(char *question, int num_knocks){
  int ch, count=0;
  int row, col;
  MEVENT event;

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  clear();
  cbreak();

  // set up NCURSES to get mouse events
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

  // get the dimensions of the screen
  getmaxyx(stdscr, row, col);
  int xtolerance = 10;
  int ytolerance = 5;

  // print the question
  mvprintw(0, 0, question);
  refresh();

  while ((ch = getch()) != 'e')
  {
    // clear and print the question
    clear();
    mvprintw(0, 0, question);
    mvprintw(7, 1, "You have knocked %d time(s)", count);

    // check and see if a mouse event has happened
    if (ch == KEY_MOUSE)
    {
      assert(getmouse(&event) == OK);
      if(event.bstate & BUTTON1_CLICKED){
        // determine if the click was in the center of the screen
        if(event.y >= (row/2)-ytolerance && event.y <= (row/2)+ytolerance){
          if(event.x >= (col/2)-xtolerance && event.x <= (col/2)+xtolerance){
            count++;
            mvprintw(7, 1, "You have knocked %d time(s)", count);
          }
        }
      }
    }
    refresh();
  }

  // return 0 for correct and 1 for incorrect
  if(count==num_knocks){
    return 0;
  }
  else{
    return 1;
  }
}
