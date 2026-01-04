#include <raylib.h>
#include <raymath.h>

const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 720;

typedef struct{
    Vector2 position;
    Vector2 offset;
    float zoom;
} customCamera;

typedef struct{
    Vector2 position;
    float speed;
} Player;


int main(){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "custom camera");
    SetTargetFPS(60);

    int mapWidth = 1000;
    int mapHeight = 800;

    Player player;
    player.position = (Vector2){640, 360};
    player.speed = 300.0f;
    customCamera cam = { 0 };
    cam.position = player.position;
    cam.offset = (Vector2){SCREENWIDTH/2.0f, SCREENHEIGHT/2.0f};
    cam.zoom = 1.0f;

    while(!WindowShouldClose()){

        float deltaTime = GetFrameTime();

        if(IsKeyDown(KEY_RIGHT)) player.position.x += player.speed * deltaTime;
        if(IsKeyDown(KEY_LEFT)) player.position.x -= player.speed * deltaTime;
        if(IsKeyDown(KEY_UP)) player.position.y -= player.speed * deltaTime;
        if(IsKeyDown(KEY_DOWN)) player.position.y += player.speed * deltaTime;

        cam.position.x = player.position.x;
        cam.position.y = player.position.y;
    }
}

