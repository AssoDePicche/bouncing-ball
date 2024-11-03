#include <raylib.h>
#include <stdlib.h>

#include "ball.h"

int main(void) {
  struct Ball *ball = (struct Ball *)malloc(sizeof(struct Ball));

  InitWindow(480, 480, "");

  SetTargetFPS(60);

  ball->center =
      (Vector2){.x = GetScreenWidth() / 2.0f, .y = GetScreenHeight() / 2.0f};

  ball->previousCenter = ball->center;

  ball->radius = 20.0f;

  ball->velocity = (Vector2){.x = 150.0f, .y = 150.0f};

  ball->friction = 0.99f;

  ball->elasticity = 0.9f;

  ball->color = BLUE;

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(WHITE);

    UpdateBall(ball);

    DrawBall(ball);

    EndDrawing();
  }

  CloseWindow();

  free(ball);

  return 0;
}
