#include <iostream>
#include <raylib.h>

using namespace std;
Color Green=Color{39,185,154,255};
Color dark_green=Color{20,160,133,255};
Color light_Green=Color{129,204,184,255};
Color yellow=Color{243,213,91,255};

int player_score=0;
int cpu_score=0;
class Ball{
    public:
    float x,y;
    int speed_x,speed_y;
    int radius;

    void Draw(){
        DrawCircle(x,y,radius,yellow);
    }
    void Update()
    {
        x +=speed_x;
        y +=speed_y;
    if(y+radius >=GetScreenHeight() || y-radius <=0){
        speed_y *=-1;
    }
    if(x+radius >=GetScreenWidth())//cpu winds
    {
        cpu_score++;
        reset_ball();
    }
     if(x-radius<=0){
        player_score++;
        reset_ball();
    
    }
    }
    void reset_ball(){
       x=GetScreenWidth()/2;
       y=GetScreenHeight()/2;
       
       int speed_choices[2]={-1,1};
       speed_x *=speed_choices[GetRandomValue(0,1)];
       speed_y *=speed_choices[GetRandomValue(0,1)];    }
};
class paddle{
    protected:
    void limit_movement(){
     if(y<=0){
     y=0;
    }
    if(y+height >=GetScreenHeight()){
        y=GetScreenHeight()-height;
    }
    }
public:
float x,y;
float width,height;
int speed;
void Draw(){
    DrawRectangleRounded(Rectangle{x,y,width,height},0.8,0,WHITE);
}
void Update(){
    if(IsKeyDown(KEY_UP)){
        y=y-speed;

    }
    if(IsKeyDown(KEY_DOWN)){
        y=y+speed;
    }
    limit_movement();
    
}



};
class CpuPaddle:public paddle{
public:
void Update(int ball_y){
    if(y+height >ball_y){
        y=y-speed;

    }
    if(y+height/2 <= ball_y){
        y=y+speed;
    }
    limit_movement();
}
};


Ball ball;
paddle Player;
CpuPaddle cpu; 
int main () {

    cout<<"starting the game:"<<endl;
    const int screen_width=1280;
    const int screen_height=800;
    InitWindow(screen_width,screen_height,"ping pong");
    SetTargetFPS(60);

    ball.radius=20;
    ball.x=screen_width/2;
    ball.y=screen_height/2;
    ball.speed_x=7;
    ball.speed_y=7;

    Player.width=25;
    Player.height=120;
    Player.x=screen_width-Player.width -10;
    Player.y=screen_height/2-Player.height/2;
    Player.speed=6;

    cpu.height=120;
    cpu.width=25;
    cpu.x=10;
    cpu.y=screen_height/2 -cpu.height/2;
    cpu.speed=6;



    while(WindowShouldClose()== false){

        BeginDrawing();
        //ball update
        ball.Update();
        Player.Update();
        cpu.Update(ball.y);
        //checking for collisiom
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{Player.x,Player.y,Player.width,Player.height}))
        {
            ball.speed_x*=-1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
        {
            ball.speed_x *=-1;
        }
//drawing
    ClearBackground(dark_green);
    DrawRectangle(screen_width/2,0,screen_width/2,screen_height,Green);
    DrawCircle(screen_width/2,screen_height/2,150,light_Green);
        DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);
        ball.Draw();
        cpu.Draw();
        
        Player.Draw();
        DrawText(TextFormat("%i",cpu_score),screen_width/4-20,20,80,WHITE);

        DrawText(TextFormat("%i",player_score),3*screen_width/4-20,20,80,WHITE);

        EndDrawing();


    }

    CloseWindow();
    return 0;
}