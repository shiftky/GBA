#include "gba.h"
#include "game.h"
#include "box.h"
#include "ball.h"
#include "racket.h"
#include "utils.h"

//#define INIT_X    100
#define INIT_X    0
#define INIT_Y    130
#define RACKET_H  4
//#define RACKET_W  35
#define RACKET_W  LCD_WIDTH
#define DISTANCE  4

static struct box racket;
static int racket_x, racket_y;

static void init_racket(void)
{
  racket_x = racket.x = INIT_X;
  racket_y = racket.y = INIT_Y;
  racket.width = RACKET_W;
  racket.height = RACKET_H;
  draw_box(&racket, racket.x, racket.y, COLOR_WHITE);
}

void racket_step(void)
{
  switch ( game_get_state() ) {
    case START:
      init_racket();
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
  }
}
