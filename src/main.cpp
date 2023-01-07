
#include "raylib.h"

// init
const size_t SCREEN_WIDTH = 1080;
const size_t SCREEN_HEIGHT = 720;

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mycotic Uprising");
    SetTargetFPS(60);

    InitAudioDevice();
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // input

        float deltaTime = GetFrameTime();

        // update

        // draw
        BeginDrawing();
            ClearBackground(SKYBLUE);
        EndDrawing();
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Unload resources

    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
