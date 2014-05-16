#include "gba.h"
#include "box.h"
#include "ball.h"

static struct box ball = { 10, 10, 5, 5 };
static struct box ball2 = { 100, 100, 5, 5 };
static struct box ball3 = { 50, 50, 5, 5 };

static int old_x = 0, old_y = 0;
static int old_x2 = 100, old_y2 = 100;
static int old_x3 = 50, old_y3 = 50;

static int dx = 2, dy = 1;
static int dx2 = 5, dy2 = 1;
static int dx3 = 3, dy3 = 1;

int ball_get_dy(void) { return dy; }
void ball_set_dy(int new_dy) { dy = new_dy; }
struct box *ball_get_box(void) { return &ball; }

void ball_step(void)
{
  int x = old_x + dx, y = old_y + dy;

  if ( y != old_y && ( y <= 0 || LCD_HEIGHT-ball.width < y )) {
    dy *= -1;
    return;
  }
  if ( x != old_x && ( x <= 0 || LCD_WIDTH-ball.width < x )) {
    dx *= -1;
    return;
  }

  move_box(&ball, x, y, COLOR_WHITE);
  old_x = x; old_y = y;
}

void ball_step2(void)
{
  int x = old_x2 + dx2, y = old_y2 + dy2;

  if ( y != old_y2 && ( y <= 0 || LCD_HEIGHT-ball2.width < y )) {
    dy2 *= -1;
    return;
  }
  if ( x != old_x2 && ( x <= 0 || LCD_WIDTH-ball2.width < x )) {
    dx2 *= -1;
    return;
  }

  move_box(&ball2, x, y, COLOR_WHITE);
  old_x2 = x; old_y2 = y;
}

void ball_step3(void)
{
  int x = old_x3 + dx3, y = old_y3 + dy3;

  if ( y != old_y3 && ( y <= 0 || LCD_HEIGHT-ball3.width < y )) {
    dy3 *= -1;
    return;
  }
  if ( x != old_x3 && ( x <= 0 || LCD_WIDTH-ball3.width < x )) {
    dx3 *= -1;
    return;
  }

  move_box(&ball3, x, y, COLOR_WHITE);
  old_x3 = x; old_y3 = y;
}
