#include <raylib.h>
#include <stdlib.h>

#include "ball.h"

int main(void) {
  InitWindow(480, 480, "");

  SetTargetFPS(60);

  struct Node *head = Node();

  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)) {
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

  CloseWindow();

  FreeNode(head);

  return 0;
}
