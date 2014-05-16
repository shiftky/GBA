#include "gba.h"
#include "box.h"

void draw_box(struct box *b, int x, int y, hword color)
{
  hword   *base, *d;
  int     w, h;

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