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
    int size;
    Color color;
} Player;

void drawMap(int mapWidth, int mapHeight, customCamera *cam){
    for (int x = 0; x < mapWidth; x+=64)
    {
        for (int y = 0; y < mapHeight; y+=64)
        {
            DrawRectangle(x-cam->position.x + cam->offset.x, y-cam->position.y + cam->offset.x, 64,64, GREEN);
        } 
    }
}

void drawPlayer(Player *player, customCamera *cam){
    DrawRectangle(player->position.x - cam->position.x + cam->offset.x, player->position.y - cam->position.y + cam->offset.y, player->size, player->size, player->color);
}

int main(){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "custom camera");
    SetTargetFPS(60);

    int mapWidth = 1000;
    int mapHeight = 800;

    Player player;
    player.position = (Vector2){640, 360};
    player.speed = 300.0f;
    player.size = 64;
    player.color = RED;

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

        BeginDrawing();

        ClearBackground(BLACK);

        drawMap(mapWidth, mapHeight, &cam);
        drawPlayer(&player, &cam);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}

