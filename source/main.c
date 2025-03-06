#include <raylib.h>
#include <stddef.h>

#include "ball.h"

__attribute((constructor)) static void setup(void) {
  InitWindow(480, 480, "");

  SetTargetFPS(60);

  SetExitKey(KEY_Q);

  SetRandomSeed(0);
}

__attribute((destructor)) static void teardown(void) { CloseWindow(); }

int main(void) {
  struct Node *head = Node();

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(WHITE);

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      head = PushFront(head);
    }

    for (struct Node *node = head; node != NULL; node = node->next) {
      UpdateBall(node->ball);

      DrawBall(node->ball);
    }

    const char *copyright = "AssoDePicche © 2024";

    const int fontSize = 16;

    const int size = MeasureText(copyright, fontSize);

    const int x = (GetScreenWidth() - size) / 2;

    DrawText(copyright, x, 40, fontSize, GRAY);

    EndDrawing();
  }

  FreeNode(head);

  return 0;
}
