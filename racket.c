#include "gba.h"
#include "box.h"
#include "ball.h"
#include "racket.h"

#define INIT_X    30
#define INIT_Y    130
#define RACKET_H  4
#define RACKET_W  35
#define DISTANCE  4

static struct box racket = { INIT_X, INIT_Y, RACKET_W, RACKET_H };
static int racket_x = INIT_X, racket_y = INIT_Y;

void racket_step(void)
{
  int key = gba_register(KEY_STATUS);

  if ( !(key & KEY_LEFT) && racket_x > 0 ) {
    if ( racket_x < DISTANCE ) {
      racket_x = 0;
    } else {
      racket_x -= DISTANCE;
    }
  } else if ( !(key & KEY_RIGHT) && racket_x < LCD_WIDTH-racket.width ) {
    if ( (racket_x + DISTANCE + racket.width) > LCD_WIDTH ) {
      racket_x = LCD_WIDTH - racket.width;
    } else {
      racket_x += DISTANCE;
    }
  }

  if ( cross(&racket, ball_get_box()) == 1 ) {
    ball_set_dy(-1 * ball_get_dy());
  }

  move_box(&racket, racket_x, racket_y, COLOR_WHITE);
}
