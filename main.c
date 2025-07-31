#include <raylib.h>
#include <stdio.h>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720
#define PADDLE_HEIGHT 15
#define PADDLE_WIDTH  100
#define PADDLE_SPEEDX 10
#define BALL_RADIUS 15
#define BLOCK_WIDTH 115
#define BLOCK_HEIGHT 50
#define BLOCKS_PER_LINE 10
#define TOTAL_BLOCKS 4 * BLOCKS_PER_LINE
#define Y_OFFSET 40

typedef struct {
    Vector2 center;
    float radius;
    float dx;
    float dy;
    Color color;
}Ball;

typedef struct  {
    Rectangle rec;
    int active;
}Block;

Rectangle paddle;
Block blocks[TOTAL_BLOCKS];

Ball ball;
int ballMoving;

void InitializeGame(void) {
    paddle.height = PADDLE_HEIGHT;
    paddle.width = PADDLE_WIDTH;
    paddle.x = (SCREENWIDTH - PADDLE_WIDTH) / 2;
    paddle.y = SCREENHEIGHT - 2 * PADDLE_HEIGHT;
    ball.radius = BALL_RADIUS;
    ball.center.x = paddle.x + PADDLE_WIDTH / 2;
    ball.center.y = paddle.y - ball.radius;
    ball.color = WHITE;
    ballMoving = 0;
    ball.dx  = 5;
    ball.dy = -5;
    
    int line = 0;
    int column = 0;
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        blocks[i].rec.height = BLOCK_HEIGHT;
        blocks[i].rec.width = BLOCK_WIDTH;
        blocks[i].active = 1;

        if (i % BLOCKS_PER_LINE == 0) {
            line++;
            column = 0;
        }
        blocks[i].rec.x = 20 + 125 * column;
        blocks[i].rec.y = Y_OFFSET + 60 * (line - 1);
        column++;
    }
}

void DrawFrame(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(paddle, WHITE);
    DrawCircleV(ball.center, ball.radius, ball.color);

    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (blocks[i].active) {
            DrawRectangleRec(blocks[i].rec, RED);
        } 
    }
    EndDrawing();
}

void CollisionDetection(void) {
    if ((ball.center.x + ball.radius) > SCREENWIDTH || (ball.center.x - ball.radius) < 0) {
        ball.dx *= -1;
    }
    if ((ball.center.y - ball.radius < 0) || CheckCollisionCircleRec(ball.center, ball.radius, paddle)) {
        ball.dy *= -1;
    }

    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (blocks[i].active) {
            if (CheckCollisionCircleRec(ball.center, ball.radius, blocks[i].rec)) {
                blocks[i].active = 0;
                ball.dy *= -1;
            }
        }
    }
}

void Update(void) {
    if (IsKeyDown(KEY_RIGHT) && paddle.x < (SCREENWIDTH - PADDLE_WIDTH)) {
        paddle.x += PADDLE_SPEEDX;
    }
    if (IsKeyDown(KEY_LEFT) && paddle.x > 0) {
        paddle.x -= PADDLE_SPEEDX;
    }
    if(IsKeyPressed(KEY_SPACE)) {
        ballMoving = 1;
    }
    if (ballMoving) {
        ball.center.x += ball.dx;
        ball.center.y += ball.dy;
    }
}

int main(void) {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Breakout");

    SetTargetFPS(60);
    
    InitializeGame();

    while (!WindowShouldClose()) {
        Update();
        CollisionDetection();
        DrawFrame();
    }
    CloseWindow();
}