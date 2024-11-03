#include <raylib.h>
#include <stdlib.h>

#include "ball.h"

int main(void) {
  InitWindow(480, 480, "");

  SetTargetFPS(60);

  struct Ball *ball = Ball();

  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)) {
    BeginDrawing();

    ClearBackground(WHITE);

    UpdateBall(ball);

    DrawBall(ball);

    EndDrawing();
  }

  CloseWindow();

  FreeBall(ball);

  return 0;
}
