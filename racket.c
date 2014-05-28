#include "gba.h"
#include "game.h"
#include "box.h"
#include "ball.h"
#include "racket.h"
#include "utils.h"

#define INIT_X    30
#define INIT_Y    130
#define RACKET_H  4
#define RACKET_W  35
#define DISTANCE  4

static struct box racket = { INIT_X, INIT_Y, RACKET_W, RACKET_H };
static int racket_x = INIT_X, racket_y = INIT_Y;

void racket_step(void)
{
  switch ( game_get_state() ) {
    case START:
      if ( get_key_state(KEY_START) ) {
        init_screen();
        game_set_state(RUNNING);
      }
      break;

    case RUNNING:
      if ( get_key_state(KEY_LEFT) && racket_x > 0 ) {
        if ( racket_x < DISTANCE ) {
          racket_x = 0;
        } else {
          racket_x -= DISTANCE;
        }
      } else if ( get_key_state(KEY_RIGHT) && racket_x < LCD_WIDTH-racket.width ) {
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
      break;

    case DEAD:
      if ( get_key_state(KEY_START) ) {
        init_screen();
        game_set_state(START);
      }
      break;

    case RESTART:
      game_set_state(RUNNING);
      break;

    case CLEAR:
      break;
  }
}
