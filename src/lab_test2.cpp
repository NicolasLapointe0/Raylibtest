#include "entrypoint.h"
#include "raylib.h"
#include <math.h>

class Ball{
    public:
    float x;
    float y;
    int speed_x;
    int speed_y;
    int radius;


void Draw(){
    DrawCircle(x,y,radius,WHITE);
}

void Update(){
    x += speed_x;
    y += speed_y;
    if(y+radius >= GetScreenHeight() || y-radius <= 0){
        speed_y *= -1;
    }
    if(x+radius >= GetScreenWidth() || x-radius <= 0){
        speed_x *= -1;
    }
}
};


Ball ball;

void raylib_start(void){
    
InitWindow(772,480, "test2");
SetTargetFPS(60);
ball.radius = 20;
ball.x = GetScreenHeight()/2;
ball.y = GetScreenWidth()/2;
ball.speed_x = 7;
ball.speed_y = 7;


while(!WindowShouldClose()){
if(IsKeyDown(KEY_ESCAPE)){
    break;
}

BeginDrawing();

ClearBackground(BLUE);

ball.Update();
ball.Draw();

EndDrawing();

}

}