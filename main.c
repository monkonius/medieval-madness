// Text-based game using the raylib game library

#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "textwrap.h"

#define MAX_LINES 6
#define MAX_CHAR 350

typedef enum GameScreen { LOGO, TITLE, INTRO, GAMEPLAY, GAMEOVER, ENDING } GameScreen;
typedef enum Introduction { INTRO1, INTRO2 } Introduction;
typedef enum StoryScreen { FORK1, FORK2, CHOICE1_1, CHOICE1_2 } StoryScreen;

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Medieval Madness");

    GameScreen currentScreen = LOGO;
    Introduction introScreen = INTRO1;
    StoryScreen storyScreen = FORK1;

    Rectangle container = { 25.0f, 50.0f, screenWidth - 50.0f, screenHeight - 250.0f };

    Font font = GetFontDefault();

    const char *proceed = "[1]: Proceed";

    int framesCounter = 0;

    int choice;

    // Load text from file
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

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        switch (currentScreen) {
            case LOGO: {
                framesCounter++;
                if (framesCounter > 300) {
                    framesCounter = 0;
                    currentScreen = TITLE;
                } else if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    framesCounter = 0;
                    currentScreen = TITLE;
                }
                break;
            }
            case TITLE: {
                if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = INTRO;
                }
                break;
            }
            case INTRO: {
                framesCounter++;
                if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    framesCounter = MAX_CHAR;
                }
                switch (introScreen) {
                    case INTRO1: {
                        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                            framesCounter = 0;
                            introScreen = INTRO2;
                        }
                        break;
                    }
                    case INTRO2:
                        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                            framesCounter = 0;
                            currentScreen = GAMEPLAY;
                        }
                        break;
                }
                break;
            }
            case GAMEPLAY: {
                framesCounter++;
                if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    framesCounter = MAX_CHAR;
                }
                switch (storyScreen) {
                    case FORK1: {
                        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                            framesCounter = 0;
                            storyScreen = CHOICE1_1;
                        } else if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) {
                            framesCounter = 0;
                            storyScreen = CHOICE1_2;
                        }
                        break;
                    }
                    case CHOICE1_1: {
                        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                            currentScreen = GAMEOVER;
                        }
                        break;
                    }
                    case CHOICE1_2: {
                        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) {
                            framesCounter = 0;
                            storyScreen = FORK2;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // For testing
            // DrawRectangleLinesEx(container, 1, MAROON);

            switch (currentScreen) {
                case LOGO: {
                    const char *presentation = "Mike Tee presents...";
                    DrawText(TextSubtext(presentation, 0, framesCounter/10), screenWidth/2.0f - MeasureText(presentation, 40)/2.0f, screenHeight/2.0f - 40, 40, MAROON);
                    break;
                }
                case TITLE: {
                    const char *title = "Medieval Madness";
                    const char *subtitle = "A text-based adventure";
                    const char *start = "Press [ENTER] or [LMB] to start";
                    DrawText(title, screenWidth/2.0f - MeasureText(title, 40)/2.0f, screenHeight/2.0f - 40, 40, MAROON);
                    DrawText(subtitle, screenWidth/2.0f - MeasureText(subtitle, 20)/2.0f, screenHeight/2.0f, 20, MAROON);
                    DrawText(start, screenWidth/2.0f - MeasureText(start, 20)/2.0f, 300, 20, LIGHTGRAY);
                    break;
                }
                case INTRO: {
                    switch (introScreen) {
                        case INTRO1: {
                            DrawTextBoxed(font, TextSubtext(gameText[0], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[0])) {
                                DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 275, 20, LIGHTGRAY);
                            }
                            break;
                        }
                        case INTRO2: {
                            DrawTextBoxed(font, TextSubtext(gameText[1], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[1])) {
                                DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 275, 20, LIGHTGRAY);
                            }
                            break;
                        }
                    }
                    break;
                }
                case GAMEPLAY: {
                    switch (storyScreen) {
                        case FORK1: {
                            const char *king = "[1]: Seek the king";
                            const char *knight = "[2]: Approach one of the knights";
                            DrawTextBoxed(font, TextSubtext(gameText[2], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[2])) {
                                DrawText(king, screenWidth/2.0f - MeasureText(king, 20)/2.0f, 275, 20, LIGHTGRAY);
                                DrawText(knight, screenWidth/2.0f - MeasureText(knight, 20)/2.0f, 300, 20, LIGHTGRAY);
                            }
                            break;
                        }
                        case CHOICE1_1: {
                            DrawTextBoxed(font, TextSubtext(gameText[3], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[3])) {
                                DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 275, 20, LIGHTGRAY);
                            }
                            break;
                        }
                        case CHOICE1_2: {
                            DrawTextBoxed(font, TextSubtext(gameText[4], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[4])) {
                                DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 275, 20, LIGHTGRAY);
                            }
                            break;
                        }
                        case FORK2: {
                            const char *spell = "[1]: Cast spell";
                            const char *potion = "[2]: Brew potion";
                            DrawTextBoxed(font, TextSubtext(gameText[5], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[5])) {
                                DrawText(spell, screenWidth/2.0f - MeasureText(spell, 20)/2.0f, 275, 20, LIGHTGRAY);
                                DrawText(potion, screenWidth/2.0f - MeasureText(potion, 20)/2.0f, 300, 20, LIGHTGRAY);
                            }
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    break;
                }
                case GAMEOVER: {
                    const char *over = "GAME OVER...";
                    DrawText(over, screenWidth/2.0f - MeasureText(over, 40)/2.0f, screenHeight/2.0f - 40, 40, MAROON);
                    break;
                }
                case ENDING: {
                    const char *ending = "Thanks for playing!";
                    DrawText(ending, screenWidth/2.0f - MeasureText(ending, 40)/2.0f, screenHeight/2.0f - 40, 40, LIGHTGRAY);
                    break;
                }
                default: {
                    break;
                }
            }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
