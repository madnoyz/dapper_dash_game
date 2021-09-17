#include "raylib.h"

int main()
{
    // initialize window
    const int windowWidth{512};
    const int windowHeight{380};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // Acceleration due to gravity (pixels/s)/s
    const int gravity{1'500};
    int velocity{0}; // pixels/frame
    
    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_sprintsheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{ windowWidth, windowHeight - nebRec.height};

    int nebVel{-600}; 

    // scarfy character variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowHeight/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int frame{0}; // animation frame
    const float updateTime{1.0 / 12.0};
    float runningTime;

    // is character in the air
    bool isInAir{};
    // jump velocity pixels/sec
    const int jumpVel{-600};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        const float dT = GetFrameTime();     

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Start game logic

        if( scarfyPos.y >= windowHeight - scarfyRec.height )
        {
            velocity = 0;
            isInAir = false;
        }
        else {
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump
        if( IsKeyDown(KEY_SPACE) && !isInAir ) {
            velocity += jumpVel;
        }

        // Update nebula position
        nebPos.x += nebVel * dT;

        // Update Scarfy position
        scarfyPos.y += velocity * dT;

        if(!isInAir) {
            runningTime += dT;
            // Update animation frame
            if( runningTime >= updateTime) 
            {
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if(frame > 5)
                {
                    frame = 0;
                }
            }
        }

        
        // Draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // Draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // End game logic

        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}