#include <raylib.h>
#include <stdlib.h>

#include "ball.h"

void DrawCopyright(void) {
  const char *copyright = "AssoDePicche © 2024";

  const int fontSize = 16;

  const int size = MeasureText(copyright, fontSize);

  const int x = (GetScreenWidth() - size) / 2;

  DrawText(copyright, x, 40, fontSize, GRAY);
}

struct Node {
  struct Node *next;
  struct Ball *ball;
};

struct Node *Node(void) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));

  if (node != NULL) {
    node->next = NULL;

    node->ball = Ball();
  }

  return node;
}

struct Node *PushFront(struct Node *head) {
  struct Node *node = Node();

  node->next = head;

  head = node;

  return head;
}

struct Node *PopFront(struct Node *head) {
  if (head == NULL) {
    return NULL;
  }

  struct Node *node = head;

  head = head->next;

  FreeBall(node->ball);

  free(node);

  return head;
}

int main(void) {
  InitWindow(480, 480, "");

  SetTargetFPS(60);

  struct Node *head = Node();

  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)) {
    BeginDrawing();

    ClearBackground(WHITE);

    DrawCopyright();

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      head = PushFront(head);
    }

    for (struct Node *node = head; node != NULL; node = node->next) {
      UpdateBall(node->ball);

      DrawBall(node->ball);
    }

    EndDrawing();
  }

  CloseWindow();

  while (head != NULL) {
    head = PopFront(head);
  }

  return 0;
}
