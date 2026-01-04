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
    DrawRectangle(
        (0 - cam->position.x) * cam->zoom + cam->offset.x,
        (0 - cam->position.y) * cam->zoom + cam->offset.y,
        mapWidth  * cam->zoom,
        mapHeight * cam->zoom,
        GREEN
    );
        
}

void drawPlayer(Player *player, customCamera *cam){
    DrawRectangle((player->position.x - cam->position.x) * cam->zoom  + cam->offset.x,
                  (player->position.y - cam->position.y) * cam->zoom  + cam->offset.y,
                   player->size * cam->zoom , player->size * cam->zoom ,
                   player->color);
}

int main(){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "camera");
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

    Vector2 lastMousePos = {0};
    bool dragging = false;

    while(!WindowShouldClose()){

        float deltaTime = GetFrameTime();

        if(IsKeyDown(KEY_RIGHT)) player.position.x += player.speed * deltaTime;
        if(IsKeyDown(KEY_LEFT)) player.position.x -= player.speed * deltaTime;
        if(IsKeyDown(KEY_UP)) player.position.y -= player.speed * deltaTime;
        if(IsKeyDown(KEY_DOWN)) player.position.y += player.speed * deltaTime;
        if (IsKeyPressed(KEY_Q)) cam.zoom *= 1.1f;
        if (IsKeyPressed(KEY_E)) cam.zoom *= 0.9f;

        cam.zoom = Clamp(cam.zoom, 0.3f, 4.0f);

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            dragging = true;
            lastMousePos = mouse;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            dragging = false;
        }

        if (dragging) {
            Vector2 delta = Vector2Subtract(mouse, lastMousePos);

            cam.position.x -= delta.x / cam.zoom;
            cam.position.y -= delta.y / cam.zoom;

            lastMousePos = mouse;
        }
        else{
            cam.position.x = player.position.x;
            cam.position.y = player.position.y;
        }
        BeginDrawing();

        ClearBackground(BLACK);

        drawMap(mapWidth, mapHeight, &cam);
        drawPlayer(&player, &cam);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}

