#include <raylib.h>
#define WIDTH 800
#define HEIGHT 600

typedef struct Circle
{
    float x;      // Circle center position x
    float y;      // Circle center position y
    float radius; // Circle radius
} Circle;

Rectangle Player = {25, HEIGHT / 2 - 50, 15, 50};
Rectangle Enemy = {WIDTH - 25 - 15, HEIGHT / 2 - 50, 15, 50};
Circle Ball = {WIDTH / 2, HEIGHT / 2, 20};

void InitScene(Rectangle *Player, Rectangle *Enemy, Circle *Ball);
void Control(Rectangle *Player);
void BallBounce(Circle *Ball, Rectangle Player, Rectangle Enemy, bool *isForward, bool *isDown);

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "PING PONG");
    SetTargetFPS(30);

    bool isForward = true;
    bool isDown = true;
    bool isPaused = false;

    while (!WindowShouldClose())
    {
        isPaused = (IsKeyPressed(KEY_P)) ? !isPaused : isPaused;
        if (!isPaused)
        {
            Control(&Player);
            BallBounce(&Ball, Player, Enemy, &isForward, &isDown);
        }
        else
        {
            DrawText("PAUSE", WIDTH / 2, HEIGHT / 2, 16, RED);
        }

        InitScene(&Player, &Enemy, &Ball);
    }
    CloseWindow();
}

void InitScene(Rectangle *Player, Rectangle *Enemy, Circle *Ball)
{
    Enemy->y = Ball->y - Enemy->height / 2;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangle(Player->x, Player->y, Player->width, Player->height, WHITE);
    DrawRectangle(Enemy->x, Enemy->y, Enemy->width, Enemy->height, WHITE);
    DrawCircle(Ball->x, Ball->y, Ball->radius, WHITE);
    EndDrawing();
}

void Control(Rectangle *Player)
{
    float speed = 6;
    if (IsKeyDown(KEY_UP) && Player->y > 0)
        Player->y -= 2 * speed;
    if (IsKeyDown(KEY_DOWN) && Player->y < (HEIGHT - Player->height))
        Player->y += 2 * speed;
}

void BallBounce(Circle *Ball, Rectangle Player, Rectangle Enemy, bool *isForward, bool *isDown)
{
    if (Ball->x <= 0 || (Ball->x >= WIDTH - Ball->radius) || CheckCollisionCircleRec((Vector2){Ball->x, Ball->y}, Ball->radius, Player) || CheckCollisionCircleRec((Vector2){Ball->x, Ball->y}, Ball->radius, Enemy))
    {
        *isForward = !(*isForward);
    }

    if (Ball->y <= 0 || (Ball->y >= HEIGHT - Ball->radius) || CheckCollisionCircleRec((Vector2){Ball->x, Ball->y}, Ball->radius, Player) || CheckCollisionCircleRec((Vector2){Ball->x, Ball->y}, Ball->radius, Enemy))
    {
        *isDown = !(*isDown);
    }

    float speed = 4;
    Ball->x += (*isForward) ? speed : -speed;
    Ball->y += (*isDown) ? speed : -speed;
}