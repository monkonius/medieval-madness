# Medieval Madness: A text-based adventure
#### Video Demo: <URL HERE>
#### Description:
*Medieval Madness* is a short text-based adventure game written in the C programming language, and makes use of the [raylib](https://www.raylib.com/) game library made by Ramon Santamaria. Visual novels like the *Ace Attorney* games were the main inspiration for creating a text adventure game for this final project, which allowed me to express creativity in the writing process as well as implement game logic along the way.

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
The decision to make a separate file for the story text was for a better designed project since hard-coding the text into `main.c` would make the code difficult to read and alter, especially when I would need to make changes later on.

The `textwrap.h` header file includes function declarations found in `textwrap.c`, which were written by Vlad Adrian for raylib demonstration purposes found [here](https://www.raylib.com/examples.html). These particular functions allow for text wrapping in accordance to a container, which I declare as follows:
```
Rectangle container = { 25.0f, 50.0f, screenWidth - 50.0f, screenHeight - 250.0f };
// Rectangle is a struct defined in raylib.h
```
I decided to just include these functions rather than directly insert them into `main.c` so that it would not clutter and lengthen the code, as well as make it easier to refer to the functions when needed.

Apart from these files, I also have a `Makefile` to aid in compiling the game and avoid having to manually type all of the arguments in the terminal every time I need to test the program.
