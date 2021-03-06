#include "gba.h"
#include "box.h"
#include "ball.h"
#include "game.h"
#include "utils.h"

#define BALL_DX   2
#define BALL_DY   1
#define BALL_COLOR BGR(31, 31, 0)

static struct box ball;
static int dx, dy, old_x, old_y, remaining;

int ball_get_remaining(void) { return remaining; }
int ball_get_dx(void) { return dx; }
int ball_get_dy(void) { return dy; }
void ball_set_dx(int new_dx) { dx = new_dx; }
void ball_set_dy(int new_dy) { dy = new_dy; }
struct box *ball_get_box(void) { return &ball; }

static void init_ball(void)
{
  ball.x = old_x = 10;
  ball.y = old_y = 60;
  ball.width = ball.height = 5;
  dx = 2; dy = 1;
}

void ball_step(void)
{
  int x, y;
  switch ( game_get_state() ) {
    case START:
      remaining = 3;
      init_ball();
      break;

    case NEXTSTAGE:
      init_ball();
      break;

    case REMAINING:
      break;

    case RUNNING:
      x = old_x + dx; y = old_y + dy;

      if ( x != old_x && ( x <= 0 || LCD_WIDTH-ball.width < x )) {
        dx = dx > 0 ? -1*BALL_DX : BALL_DX;
        return;
      }

      if ( y != old_y && y <= 0 ) {
        dy = dy > 0 ? -1*BALL_DY : BALL_DY;
        return;
      } else if ( y!= old_y && LCD_HEIGHT-ball.width < y ) {
        if ( remaining <= 1 ) {
          game_set_state(DEAD);
        } else {
          draw_box(&ball, ball.x, ball.y, COLOR_BLACK);
          remaining--;
          init_ball();
          game_set_state(REMAINING);
        }
        return;
      }

      move_box(&ball, x, y, BALL_COLOR);
      old_x = x; old_y = y;
      break;

    case CLEAR:
      draw_box(&ball, old_x, old_y, BALL_COLOR);
      break;

    case DEAD:
      break;

    case RESTART:
      remaining = 3;
      init_ball();
      break;
  }
}
