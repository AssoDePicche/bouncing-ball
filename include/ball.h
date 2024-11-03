#ifndef __BALL__
#define __BALL__

#include <raylib.h>
#include <stdbool.h>

struct Ball {
  Vector2 center;
  Vector2 previousCenter;
  Vector2 velocity;
  Color color;
  float radius;
  float friction;
  float elasticity;
  bool floating;
};

bool CollideWithPoint(const struct Ball *, const Vector2);

void DrawBall(const struct Ball *);

void UpdateBall(struct Ball *);

#endif
