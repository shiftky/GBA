#include "gba.h"
#include "game.h"
#include "box.h"
#include "ball.h"
#include "racket.h"
#include "utils.h"

#define INIT_X    100
#define INIT_Y    130
#define RACKET_H  5
#define RACKET_W  50
#define DISTANCE  4
#define RACKET_COLOR BGR(24, 8, 8)
#define BALL_DX   2
#define BALL_DY   1
#define BALL_EDGE_DX  3
#define BALL_EDGE_DY  1
#define RACKET_L_EDGE   10
#define RACKET_R_EDGE   RACKET_W - 10

static struct box racket;
static int racket_x, racket_y;

static void init_racket(void)
{
  racket_x = racket.x = INIT_X;
  racket_y = racket.y = INIT_Y;
  racket.width = RACKET_W;
  racket.height = RACKET_H;
  draw_box(&racket, racket.x, racket.y, RACKET_COLOR);
}

void racket_step(void)
{
  struct box *ball;
  switch ( game_get_state() ) {
    case START:
      init_racket();
      break;

    case NEXTSTAGE:
      init_racket();
      break;

    case REMAINING:
      draw_box(&racket, racket.x, racket.y, COLOR_BLACK);
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

      ball = ball_get_box();
      if ( cross(&racket, ball) >= 1 ) {
        if ( (ball->y+ball->height-1) <= racket_y ) {
          ball_set_dy( ball_get_dy() < 0 ? BALL_DY : -1 * BALL_DY );
          if ( (ball->x+(ball->width-1)/2) <= (racket_x+RACKET_L_EDGE) ) {
            ball_set_dx( ball_get_dx() > 0 ? -1*BALL_EDGE_DX : -1*BALL_DX );
          }
          else if ( (racket_x+RACKET_R_EDGE) <= (ball->x+(ball->width-1)/2) ){
            ball_set_dx( ball_get_dx() < 0 ? BALL_EDGE_DX : BALL_DX );
          }
        } else {
          ball_set_dx( ball_get_dx() < 0 ? BALL_DX : -1 * BALL_DX );
        }
      }

      move_box(&racket, racket_x, racket_y, RACKET_COLOR);
      break;

    case CLEAR:
      break;

    case DEAD:
      break;

    case RESTART:
      init_racket();
      break;
  }
}
