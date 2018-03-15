# Escape the Room Game
### Vicky McDermott

## Project Vision
For this project I created an interactive, text-based game in the terminal. It is an “escape room” game, where the player tries different interaction commands to escape the room. I made use of multiple choice questions, free response questions, and mouse clicking questions to make the game interactive and interesting in different ways. If a player answers a question incorrectly, they lose the game and are told they did not successfully escape the room. If they make it through all the questions correctly a message will display telling them that they have successfully escaped.

## Learning Goals
I wanted to learn more about strings and how strings work in C. I wanted to learn about how we can manipulate strings and how pointers to strings and char arrays work. I created functions that pass string pointers for questions and options. This both helped the code to be more clean and helped me to learn more about working with string pointers in C. In particular, when working with an array of strings for the multiple choice question options, I found that I learned a lot about how strings are interpreted and stored in C. I also made use of the fact that letters in C can just be represented by their ASCII numbers to help me create the corresponding letter choices for the multiple choice questions.

## Resources
NCURSES is a library of functions which manages the display for applications which are running on the terminal.

I used a tutorial that I found online for NCURSES: [NCURSES introduction](https://invisible-island.net/ncurses/ncurses-intro.html).

Another great resource that I used to learn more about NCURSES is this online tutorial: [NCURSES Tutorial](http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/).

## Accomplishments
In the end, I was able to create a basic escape the room game with 3 question types. One question type allows the user to choose an option from a multiple choice menu, one question type allows the user to type in an answer to a free response question, and the last question type asks the user to use the mouse to click on the center of the terminal a certain number of times. Because I wanted to learn more about strings for this project, I decided to split my code into functions representing each question type which can be found in 'questions.c'. This way, the question can be set from inside main and parameters for the question text and correct answer can be passed into the functions which control the question. Below for example is a picture of my code for setting up a free response question.

[](fr_question.jpg)

As you can see, my function takes in pointers to strings representing the question and the correct answer. I print the question and get the response using "getnstr(resp, 6)". This function will only allow the user to type a max of 6 characters so that I do not write past the end of the resp array. I then return 0 if the user got the correct answer or 1 otherwise.

put gamesetup.jpg right here

In the above main code from 'game.c', I setup the escape the room game. I call my multiple choice function, then my free response question, and finally, my mouse clicking question. After each question, I check to see whether there is a loss and if there is I run my losing function to end the game. If they get all the way to the end without losing, I run my win function which can be seen below.

put win.jpg right here

The first step in completing the escape the room game is to answer the multiple choice question which is displayed below. I made use of an NCURSES window to place on top of the main terminal window to display that menu.

If the user answers the first question correctly, then they are directed to this second question which is a free response question. To answer this question, the user must type in their response and press enter.

Lastly, if the user makes it to the last question, they are told to "knock on the door" and they need to figure out how many times to knock. They can knock by using their mouse to click on the center of the terminal window and enter that they are done by pressing the 'e' key.

## Reflection
