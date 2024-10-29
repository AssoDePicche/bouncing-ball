#ifndef __BALL__
#define __BALL__

#include <raylib.h>

struct Ball {
  Vector2 center;
  Vector2 velocity;
  Color color;
  float radius;
  float friction;
  float elasticity;
};

void DrawBall(const struct Ball *);

void UpdateBall(struct Ball *);

#endif
