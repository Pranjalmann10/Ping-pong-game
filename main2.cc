#include "raylib.h"

#define MAX_SNAKE_LENGTH 256
#define GRID_SIZE 20

typedef struct Snake {
    Vector2 position[MAX_SNAKE_LENGTH];
    int length;
    Vector2 speed;
} Snake;

typedef struct Food {
    Vector2 position;
    bool active;
} Food;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(10);

    Snake snake = { 0 };
    snake.position[0] = (Vector2){ screenWidth / 2, screenHeight / 2 };
    snake.length = 1;
    snake.speed = (Vector2){ GRID_SIZE, 0 };

    Food food = { 0 };
    food.active = false;

    while (!WindowShouldClose()) {
        if (!food.active) {
            food.position.x = GetRandomValue(0, screenWidth / GRID_SIZE - 1) * GRID_SIZE;
            food.position.y = GetRandomValue(0, screenHeight / GRID_SIZE - 1) * GRID_SIZE;
            food.active = true;
        }

        if (IsKeyPressed(KEY_UP) && snake.speed.y == 0) snake.speed = (Vector2){ 0, -GRID_SIZE };
        if (IsKeyPressed(KEY_DOWN) && snake.speed.y == 0) snake.speed = (Vector2){ 0, GRID_SIZE };
        if (IsKeyPressed(KEY_LEFT) && snake.speed.x == 0) snake.speed = (Vector2){ -GRID_SIZE, 0 };
        if (IsKeyPressed(KEY_RIGHT) && snake.speed.x == 0) snake.speed = (Vector2){ GRID_SIZE, 0 };

        for (int i = snake.length - 1; i > 0; i--)
            snake.position[i] = snake.position[i - 1];

        snake.position[0].x += snake.speed.x;
        snake.position[0].y += snake.speed.y;

        if (CheckCollisionRecs((Rectangle){ snake.position[0].x, snake.position[0].y, GRID_SIZE, GRID_SIZE },
                               (Rectangle){ food.position.x, food.position.y, GRID_SIZE, GRID_SIZE })) {
            snake.length++;
            food.active = false;
        }

        for (int i = 1; i < snake.length; i++) {
            if (CheckCollisionRecs((Rectangle){ snake.position[0].x, snake.position[0].y, GRID_SIZE, GRID_SIZE },
                                   (Rectangle){ snake.position[i].x, snake.position[i].y, GRID_SIZE, GRID_SIZE })) {
                snake.length = 1;
                snake.position[0] = (Vector2){ screenWidth / 2, screenHeight / 2 };
                snake.speed = (Vector2){ GRID_SIZE, 0 };
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < snake.length; i++)
            DrawRectangle(snake.position[i].x, snake.position[i].y, GRID_SIZE, GRID_SIZE, DARKGREEN);

        if (food.active) DrawRectangle(food.position.x, food.position.y, GRID_SIZE, GRID_SIZE, RED);

        DrawRectangleLines(0, 0, screenWidth, screenHeight, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
