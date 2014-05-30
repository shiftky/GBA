#include "gba.h"
#include "utils.h"
#include "box.h"

void draw_box(struct box *b, int x, int y, hword color)
{
  hword *base, *d;
  int w, h;

  /* Base point is at (x, y). */
  base = (hword*)VRAM + LCD_WIDTH * y + x;

  /* Draw box from (x, y). */
  for (h = b->height; h > 0; h--) {
    d = base;
    for (w = b->width; w > 0; w--) {
      *(d++) = color;
    }
    base += LCD_WIDTH;
  }

  /* Set the current position. */
  b->x = x;
  b->y = y;
}

void move_box(struct box *b, int x, int y, hword color)
{
  draw_box(b, b->x, b->y, COLOR_BLACK);
  draw_box(b, x, y, color);
}

int cross(struct box *b1, struct box *b2)
{
  if ((b1->x <= b2->x+b2->width-1 && b1->x+b1->width-1 >= b2->x) && (b1->y <= b2->y+b2->height-1 && b1->y+b1->height-1 >= b2->y)) {
    return 1;
  } else {
    return 0;
  }
}
