# Medieval Madness: A text-based adventure
#### Video Demo: <URL HERE>
#### Description:
Medieval Madness is a short text-based adventure game written in the C programming language, and makes use of the [raylib](https://www.raylib.com/) game library. Visual novels like the Ace Attorney games were the main inspiration for creating a text adventure game for this final project, which allowed me to express creativity in the writing process as well as figure out how to implement game logic.

`main.c` is where most of the logic resides, including loading story text to memory from `story.txt`. The `textwrap.h` header file includes function declarations found in `textwrap.c`, which were written by Vlad Adrian for raylib demonstration purposes found [here](https://www.raylib.com/examples.html). These particular functions allow for text wrapping in accordance to a container. Apart from these files, I also wrote a `Makefile` to aid in compiling the game.
