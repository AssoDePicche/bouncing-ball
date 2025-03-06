#ifndef __BALL__
#define __BALL__

#include <raylib.h>
#include <stdbool.h>

struct Ball;

struct Ball *Ball(void);

void FreeBall(struct Ball *);

bool CollideWithPoint(const struct Ball *, const Vector2);

bool CollideWithBall(const struct Ball *, const struct Ball *);

Vector2 GetCollisionForce(const struct Ball *, const struct Ball *);

void ApplyForce(struct Ball *, const Vector2);

void DrawBall(const struct Ball *);

void UpdateBall(struct Ball *);

#endif
