// Text-based game using the raylib game library

#include "raylib.h"
#include "textwrap.h"

typedef enum GameScreen {
    LOGO = 0,
    TITLE,
    INTRO,
    ENDING
} GameScreen;

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Placeholder Title");

    GameScreen currentScreen = LOGO;

    Rectangle container = { 25.0f, 25.0f, screenWidth - 50.0f, screenHeight - 200.0f };

    Font font = GetFontDefault();

    int framesCounter = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        switch (currentScreen) {
            case LOGO:
                framesCounter++;
                if (framesCounter > 300) {
                    framesCounter = 0;
                    currentScreen = TITLE;
                } else if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    framesCounter = 0;
                    currentScreen = TITLE;
                }
                break;
            case TITLE:
                if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = INTRO;
                }
                break;
            case INTRO:
                framesCounter++;
                if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = ENDING;
                }
                break;
            default:
                break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // For testing
            DrawRectangleLinesEx(container, 1, MAROON);

            switch (currentScreen) {
                case LOGO:
                    const char *presentation = "Mike Tee presents...";
                    DrawText(TextSubtext(presentation, 0, framesCounter/10), screenWidth/2.0f - MeasureText(presentation, 40)/2.0f, screenHeight/2.0f - 40, 40, MAROON);
                    break;
                case TITLE:
                    const char *title = "Placeholder Title";
                    const char *subtitle = "A text-based adventure";
                    const char *proceed = "Press [ENTER] or [LMB] to start";
                    DrawText(title, screenWidth/2.0f - MeasureText(title, 40)/2.0f, screenHeight/2.0f - 40, 40, MAROON);
                    DrawText(subtitle, screenWidth/2.0f - MeasureText(subtitle, 20)/2.0f, screenHeight/2.0f, 20, MAROON);
                    DrawText(proceed, screenWidth/2.0f - MeasureText(proceed, 20)/2.0f, 300, 20, LIGHTGRAY);
                    break;
                case INTRO:
                    const char *introduction = "You were on your way home one night from the nearby convenience store when all of a sudden, a deep fog surrounds you. "
                    "Confused, you try to feel your way through the fog. You feel a rather unfamiliar stone-like surface. When the fog clears, you then realize you're "
                    "in a medieval castle, surrounded by knights.\n\nYou've been transported back to the middle ages! Find your way back home!";
                    DrawTextBoxed(font, TextSubtext(introduction, 0, framesCounter), (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, true, DARKGRAY);
                    break;
                case ENDING:
                    const char *ending = "Thanks for playing!";
                    DrawText(ending, screenWidth/2.0f - MeasureText(ending, 40)/2.0f, screenHeight/2.0f - 40, 40, LIGHTGRAY);
                    break;
                default:
                    break;
            }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
