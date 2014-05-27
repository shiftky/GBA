#include "gba.h"
#include "box.h"
#include "ball.h"
#include "game.h"

static struct box ball = { 10, 10, 5, 5 };
static int old_x = 0, old_y = 0;
static int dx = 2, dy = 1;

int ball_get_dy(void) { return dy; }
void ball_set_dy(int new_dy) { dy = new_dy; }
struct box *ball_get_box(void) { return &ball; }

void ball_step(void)
{
  int x = old_x + dx, y = old_y + dy;

  switch ( game_get_state() ) {
    case START:
      break;
    case RUNNING:
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
      break;
    case DEAD:
      break;
    case RESTART:
      break;
  }
}
