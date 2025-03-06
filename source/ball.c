#include "ball.h"

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

bool CollideWithScreenEdges(const struct Ball *this) {
  const bool right = CollideWithScreenRight(this);

  const bool left = CollideWithScreenLeft(this);

  const bool top = CollideWithScreenTop(this);

  const bool bottom = CollideWithScreenBottom(this);

  return right || left || top || bottom;
}

bool CollideWithPoint(const struct Ball *this, const Vector2 point) {
  const float dx = point.x - this->center.x;

  const float dy = point.y - this->center.y;

  return dx * dx + dy * dy <= this->radius * this->radius;
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

  if (CollideWithScreenEdges(this) && !CollideWithScreenBottom(this)) {
    this->color = GetRandomColor();
  }

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

struct Node *Node(void) {
  struct Node *node = (struct Node *)MemAlloc(sizeof(struct Node));

  if (node != NULL) {
    node->next = NULL;

    node->ball = Ball();
  }

  return node;
}

void FreeNode(struct Node *this) {
  while (NULL != this) {
    this = PopFront(this);
  }
}

struct Node *PushFront(struct Node *this) {
  struct Node *node = Node();

  node->next = this;

  this = node;

  return this;
}

struct Node *PopFront(struct Node *this) {
  if (this == NULL) {
    return NULL;
  }

  struct Node *node = this;

  this = this->next;

  FreeBall(node->ball);

  MemFree(node);

  return this;
}
