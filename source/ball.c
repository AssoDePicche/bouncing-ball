#include "ball.h"

#include <math.h>
#include <raymath.h>
#include <stddef.h>

struct Ball {
  Vector2 center;
  Vector2 previousCenter;
  Vector2 velocity;
  Color color;
  float radius;
  float friction;
  float elasticity;
  float mass;
  bool floating;
};

const float WORLD_GRAVITY = 9.81f;

static Color GetRandomColor(void) {
  return (Color){
      .r = GetRandomValue(0, 255),
      .g = GetRandomValue(0, 255),
      .b = GetRandomValue(0, 255),
      .a = 255,
  };
}

static bool CollideWithScreenRight(const struct Ball *this) {
  return GetScreenWidth() < this->center.x + this->radius;
}

static bool CollideWithScreenLeft(const struct Ball *this) {
  return this->center.x - this->radius <= 0.0f;
}

static bool CollideWithScreenTop(const struct Ball *this) {
  return this->center.y - this->radius <= 0.0f;
}

static bool CollideWithScreenBottom(const struct Ball *this) {
  return GetScreenHeight() < this->center.y + this->radius;
}

struct Ball *Ball(void) {
  struct Ball *this = (struct Ball *)MemAlloc(sizeof(struct Ball));

  if (NULL == this) {
    return NULL;
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    this->center = (Vector2){
        .x = GetMouseX() % GetScreenWidth(),
        .y = GetMouseY() % GetScreenHeight(),
    };
  } else {
    this->center = (Vector2){
        .x = GetScreenWidth() / 2.0f,
        .y = GetScreenHeight() / 2.0f,
    };
  }

  this->previousCenter = this->center;

  this->radius = GetRandomValue(20, 35);

  this->velocity = (Vector2){
      .x = 0.0f,
      .y = GetRandomValue(100.0f, 200.0f),
  };

  this->friction = 0.99f;

  this->elasticity = 0.9f;

  this->mass = GetRandomValue(1.0f, 5.0f);

  this->color = GetRandomColor();

  return this;
}

void FreeBall(struct Ball *this) {
  if (NULL == this) {
    return;
  }

  MemFree(this);
}

bool CollideWithPoint(const struct Ball *this, const Vector2 point) {
  const float dx = point.x - this->center.x;

  const float dy = point.y - this->center.y;

  return dx * dx + dy * dy <= this->radius * this->radius;
}

bool CollideWithBall(const struct Ball *this, const struct Ball *other) {
  return CheckCollisionCircles(this->center, this->radius, other->center,
                               other->radius);
}

Vector2 GetCollisionForce(const struct Ball *this, const struct Ball *other) {
  if (!CollideWithBall(this, other)) {
    return Vector2Zero();
  }

  const float dx = (this->center.x - other->center.x);

  const float dy = (this->center.y - other->center.y);

  const float r = sqrt(dx * dx + dy * dy);

  const float force = (WORLD_GRAVITY * this->mass * other->mass) / r * r;

  return (Vector2){
      .x = (dx / r) * force / this->mass,
      .y = (dy / r) * force / this->mass,
  };
}

void ApplyForce(struct Ball *this, const Vector2 force) {
  this->velocity.x += force.x;

  this->velocity.y += force.y;
}

void DrawBall(const struct Ball *this) {
  DrawCircle((int)this->center.x, (int)this->center.y, this->radius,
             this->color);
}

void UpdateBall(struct Ball *this) {
  const float frameTime = GetFrameTime();

  const Vector2 point = (Vector2){
      .x = GetMouseX(),
      .y = GetMouseY(),
  };

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CollideWithPoint(this, point)) {
    this->floating = true;
  }

  if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
    this->floating = false;
  }

  if (this->floating) {
    this->center = GetMousePosition();

    this->velocity.x = (this->center.x - this->previousCenter.x) / frameTime;

    this->velocity.y = (this->center.y - this->previousCenter.y) / frameTime;

    this->previousCenter = this->center;

    return;
  }

  this->center.x += this->velocity.x * frameTime;

  this->center.y += this->velocity.y * frameTime;

  if (CollideWithScreenLeft(this) || CollideWithScreenRight(this)) {
    this->velocity.x = -this->velocity.x * this->elasticity;
  }

  if (CollideWithScreenBottom(this) || CollideWithScreenTop(this)) {
    this->velocity.y = -this->velocity.y * this->elasticity;
  }

  if (CollideWithScreenRight(this)) {
    this->center.x = GetScreenWidth() - this->radius;
  }

  if (CollideWithScreenLeft(this)) {
    this->center.x = this->radius;
  }

  if (CollideWithScreenBottom(this)) {
    this->center.y = GetScreenHeight() - this->radius;
  }

  if (CollideWithScreenTop(this)) {
    this->center.y = this->radius;
  }

  this->velocity.x = this->velocity.x * this->friction;

  this->velocity.y =
      this->velocity.y * this->friction + WORLD_GRAVITY * this->mass;
}
