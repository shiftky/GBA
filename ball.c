#include "gba.h"
#include "box.h"
#include "ball.h"
#include "game.h"
#include "utils.h"

static struct box ball;
static int dx, dy, old_x, old_y;

int ball_get_dy(void) { return dy; }
void ball_set_dy(int new_dy) { dy = new_dy; }
struct box *ball_get_box(void) { return &ball; }

static void ball_init(void)
{
  ball.x = old_x = 100; ball.y = old_y = 100;
  ball.width = 5; ball.height = 5;
  dx = 2; dy = -1;
}

void ball_step(void)
{
  int x = old_x + dx, y = old_y + dy;
  switch ( game_get_state() ) {
    case START:
      ball_init();
      break;

    case RUNNING:
      if ( y != old_y && y <= 0 ) {
        dy *= -1;
        return;
      } else if ( y!= old_y && LCD_HEIGHT-ball.width < y ) {
        game_set_state(DEAD);
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

    case CLEAR:
      break;
  }
}
