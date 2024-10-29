#include "ball.h"

const float WORLD_GRAVITY = 9.81f;

void DrawBall(const struct Ball *ball) {
  DrawCircle((int)ball->center.x, (int)ball->center.y, ball->radius,
             ball->color);
}

void UpdateBall(struct Ball *ball) {
  const float frameTime = GetFrameTime();

  ball->center.x += ball->velocity.x * frameTime;

  ball->center.y += ball->velocity.y * frameTime;

  if (GetScreenWidth() < ball->center.x + ball->radius) {
    ball->center.x = GetScreenWidth() - ball->radius;

    ball->velocity.x = -ball->velocity.x * ball->elasticity;
  }

  if (ball->center.x - ball->radius <= 0.0f) {
    ball->center.x = ball->radius;

    ball->velocity.x = -ball->velocity.x * ball->elasticity;
  }

  if (GetScreenHeight() < ball->center.y + ball->radius) {
    ball->center.y = GetScreenHeight() - ball->radius;

    ball->velocity.y = -ball->velocity.y * ball->elasticity;
  }

  if (ball->center.y - ball->radius <= 0.0f) {
    ball->center.y = ball->radius;

    ball->velocity.y = -ball->velocity.y * ball->elasticity;
  }

  ball->velocity.x = ball->velocity.x * ball->friction;

  ball->velocity.y = ball->velocity.y * ball->friction + WORLD_GRAVITY;
}
