// Text-based game using the raylib game library

#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "textwrap.h"

#define MAX_LINES 3
#define MAX_CHAR 350

typedef enum GameScreen {
    LOGO = 0,
    TITLE,
    INTRO,
    GAMEPLAY,
    ENDING
} GameScreen;

typedef enum StoryNode {
    NODE1 = 0,
    NODE2,
    NODE3
} StoryNode;

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Medieval Madness");

    GameScreen currentScreen = LOGO;

    int introScreen = 0;

    Rectangle container = { 25.0f, 25.0f, screenWidth - 50.0f, screenHeight - 200.0f };

    Font font = GetFontDefault();

    int framesCounter = 0;

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
                    framesCounter = strlen(gameText[0]);
                }
                int choice = GetKeyPressed();
                switch (introScreen) {
                    case 0: {
                        if (choice == KEY_ONE || choice == KEY_KP_1) {
                            framesCounter = 0;
                            introScreen = 1;
                        }
                        break;
                    }
                    case 1:
                        if (choice == KEY_ONE || choice == KEY_KP_1) {
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
                    currentScreen = ENDING;
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
            DrawRectangleLinesEx(container, 1, MAROON);

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
                    const char *proceed = "[1]: Proceed";
                    switch (introScreen) {
                        case 0: {
                            DrawTextBoxed(font, TextSubtext(gameText[0], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[0])) {
                                DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 300, 20, LIGHTGRAY);
                            }
                            break;
                        }
                        case 1: {
                            DrawTextBoxed(font, TextSubtext(gameText[1], 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                            if (framesCounter >= strlen(gameText[1])) {
                                DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 300, 20, LIGHTGRAY);
                            }
                            break;
                        }
                    }
                    break;
                }
                case GAMEPLAY: {
                    const char *prompt = "What shall you do?";
                    DrawTextBoxed(font, TextSubtext(prompt, 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
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
