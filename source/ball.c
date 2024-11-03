#include "ball.h"

const float WORLD_GRAVITY = 9.81f;

bool CollideWithPoint(const struct Ball *ball, const Vector2 point) {
  const float dx = point.x - ball->center.x;

  const float dy = point.y - ball->center.y;

  return dx * dx + dy * dy <= ball->radius * ball->radius;
}

void DrawBall(const struct Ball *ball) {
  DrawCircle((int)ball->center.x, (int)ball->center.y, ball->radius,
             ball->color);
}

void UpdateBall(struct Ball *ball) {
  const float frameTime = GetFrameTime();

  const Vector2 point = (Vector2){.x = GetMouseX(), .y = GetMouseY()};

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CollideWithPoint(ball, point)) {
    ball->floating = true;
  }

  if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
    ball->floating = false;
  }

  if (ball->floating) {
    ball->center = GetMousePosition();

    ball->velocity.x = (ball->center.x - ball->previousCenter.x) / frameTime;

    ball->velocity.y = (ball->center.y - ball->previousCenter.y) / frameTime;

    ball->previousCenter = ball->center;

    return;
  }

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
