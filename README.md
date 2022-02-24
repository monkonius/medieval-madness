# Medieval Madness: A text-based adventure
#### Video Demo: https://youtu.be/Z_EBlKSC5TA
#### Description:
*Medieval Madness* is a short text-based adventure game written in the C programming language, and makes use of the [raylib](https://www.raylib.com/) game library made by Ramon Santamaria. Visual novels like the *Ace Attorney* games were the main inspiration for creating a text adventure game for this final project, which allowed me to express creativity in the writing process as well as implement game logic along the way.

The game was written incrementally in order to have easier testing and debugging, where I was able to quickly identify and fix bugs and unexpected behavior. This worked well even though I was working on my own given the relatively small scale of the game.

`main.c` is where most of the logic resides, including loading story text to memory from `story.txt`. This is achieved by opening the file and storing each line of text into an array of strings, illustrated here:
```
char gameText[MAX_LINES][MAX_CHAR];
char buffer[MAX_CHAR];
FILE *fp;
fp = fopen("story.txt", "r");
if (fp == NULL) {
    return 1;
}
int i = 0;
while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    strcpy(gameText[i], buffer);
    i++;
}
```
The decision to make a separate file for the story text was for a better designed project since hard-coding the text into `main.c` would make the code difficult to read and alter, especially when I would need to make changes later on. Writing the story was also easier this way since I did not need to navigate through the game's source code just to add more lines of text to the story.

As for the game logic, I defined some `enum` datatypes to differentiate the sections of the game as follows:
```
typedef enum GameScreen { LOGO, TITLE, INTRO, GAMEPLAY, GAMEOVER, ENDING } GameScreen;
typedef enum Introduction { INTRO1, INTRO2 } Introduction;
typedef enum StoryScreen { FORK1, FORK2, CHOICE1_1, CHOICE1_2, CHOICE2_1, CHOICE2_2, FINAL } StoryScreen;
```
Some of these sections fall under other ones, such as the case where `GAMEPLAY` contains the `StoryScreen` elements. These were helpful when it came to the nested `switch` statements to jump from one section to the other since I could easily refer to them. This allowed for more readable code since I could easily understand what each `case` block was for. Speaking of `switch` statements, they were used since I did not want to have multiple `if` `else if` and `else` statements in the code, where each of those conditional statements would have to be evaluated while the game ran. This would have made the game do much more than it needed to do.

The `textwrap.h` header file includes function declarations found in `textwrap.c`, which were written by Vlad Adrian for raylib demonstration purposes found [here](https://www.raylib.com/examples.html). These particular functions allow for text wrapping in accordance to a container, which I declare as follows:
```
Rectangle container = { 25.0f, 50.0f, screenWidth - 50.0f, screenHeight - 250.0f };
// Rectangle is a struct defined in raylib.h
```
These particular functions were helpful since I did not have to manually determine where each newline had to be inserted in the story text, which would have taken a much longer time given that I would have to deal with multiple lines of text. I then decided to just include these functions rather than directly insert them into `main.c` so that it would not clutter and lengthen the code, as well as make it easier to refer to the functions when needed.

Apart from these files, I also have a `Makefile` to aid in compiling the game and avoid having to manually type all of the arguments in the terminal each time I needed to test the program.
