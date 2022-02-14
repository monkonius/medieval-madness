// Text-based game using the raylib game library

#include "raylib.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Placeholder Title");

    GameScreen currentScreen = LOGO;

    int framesCounter = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        switch (currentScreen) {
            case LOGO:
                framesCounter++;
                if (framesCounter > 300) {
                    currentScreen = TITLE;
                } else if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = TITLE;
                }
                break;
            case TITLE:
                if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = GAMEPLAY;
                }
                break;
            case GAMEPLAY:
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
                case GAMEPLAY:
                    const char *message = "Gameplay to be added soon...";
                    DrawText(message, screenWidth/2.0f - MeasureText(message, 40)/2.0f, screenHeight/2.0f - 40, 40, LIGHTGRAY);
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
