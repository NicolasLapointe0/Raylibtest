#include "entrypoint.h"
#include "raylib.h"
#include <math.h>

void raylib_start(void){
    
InitWindow(772,480, "test");
SetTargetFPS(60);
float dt = GetFrameTime();
float y = 210.0f;
float x = 335.0f;


while(!WindowShouldClose()){
if(IsKeyDown(KEY_ESCAPE)){
    break;
}

BeginDrawing();

ClearBackground(BLUE);

DrawRectangle(x,y,48,48, RED);
DrawText(TextFormat("X = %0.0f et Y = %0.0f",x,y),x-40-4,y+50,15,BLACK);

if(IsKeyDown(KEY_W)){
    y += 20;
}

if(IsKeyDown(KEY_S)){
    y -= 20;
}

if(IsKeyDown(KEY_D)){
    x -= 20;
}

if(IsKeyDown(KEY_A)){
    x += 20;
}

if(x <= 0){
    x = 720;
}

if(x > 720){
    x = 0;
} 

if(y <= 0){
    y = 480;
}

if(y > 480){
    y = 0;
} 

EndDrawing();

}

}