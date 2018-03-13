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
    printw("Congratulations! You escaped!\n");
    return 1;
  }
  else{
    printw("Sorry, that's not right. Lose 1 life.\n");
    return 0;
  }

}

/* Sets up an NCURSES free response question
 *
 * question: text of the question as a string
 * answer: string that represents correct input
 */
int fr_question(char *question, char *answer){
  char escape[] = "Congrats! You escaped!";
  char no_escape[] = "Sorry, you did not escape.";
  char resp[5];
  int row, col;

  // get the dimensions of the screen
  getmaxyx(stdscr, row, col);

  // print the question in the center of the window
  clear();
  mvprintw(row/2, (col-strlen(question))/2, "%s", question);
  mvprintw((row/2)+3, (col-strlen(question))/2, "");

  // get the input response and determine if right (return 0) or wrong (return 1)
  getnstr(resp, 4);
  clear();
  if(strcmp(resp, answer) == 0){
    mvprintw(row/2, (col-strlen(escape))/2, "%s", escape);
    return 0;
  }
  else{
    mvprintw(row/2, (col-strlen(no_escape))/2, "%s", no_escape);
    return 1;
  }
}

int mouse_question(){
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
  return 0;
}
