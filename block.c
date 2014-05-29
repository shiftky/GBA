#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
#include "utils.h"

#define BLOCK_COLS    8
#define BLOCK_ROWS    7
#define BLOCK_TOP     10
#define BLOCK_LEFT    20
#define BLOCK_WIDTH   25
#define BLOCK_HEIGHT  6

static struct box boxes[BLOCK_COLS][BLOCK_ROWS];
static char flags[BLOCK_COLS][BLOCK_ROWS];
static int num_blocks;

static void init_block(void)
{
  int i, j;
  num_blocks = BLOCK_COLS * BLOCK_ROWS;
  for ( i=0; i<BLOCK_COLS; i++ ) {
    for ( j=0; j<BLOCK_ROWS; j++ ) {
      boxes[i][j].x = 20 + i*BLOCK_WIDTH;
      boxes[i][j].y = BLOCK_TOP + j*BLOCK_HEIGHT;
      boxes[i][j].width = BLOCK_WIDTH - 1;
      boxes[i][j].height = BLOCK_HEIGHT - 1;
      flags[i][j] = 1;
      draw_box(&boxes[i][j], boxes[i][j].x, boxes[i][j].y, COLOR_WHITE);
    }
  }
}

static int hit(int x, int y)
{
  int i = (x-BLOCK_LEFT)/BLOCK_WIDTH, j = (y-BLOCK_TOP)/BLOCK_HEIGHT;
  if ( i < 0 || j < 0 || i >= BLOCK_COLS || j >= BLOCK_ROWS ) {
    return -1;
  }
  return flags[i][j];
}

void remove_block(int x, int y, struct box *ball)
{
  int i = (x-BLOCK_LEFT)/BLOCK_WIDTH, j = (y-BLOCK_TOP)/BLOCK_HEIGHT;
  if ( cross(&boxes[i][j], ball) == 1 ) {
    ball_set_dy(-1 * ball_get_dy());
    flags[i][j] = 0;
    draw_box(&boxes[i][j], boxes[i][j].x, boxes[i][j].y, COLOR_BLACK);
    num_blocks--;
  }
}

void block_step(void)
{
  struct box *ball;
  switch ( game_get_state() ) {
    case START:
      init_block();
      break;

    case RUNNING:
      ball = ball_get_box();
      if ( hit(ball->x, ball->y) ) { remove_block(ball->x, ball->y, ball); }
      if ( hit(ball->x+ball->width, ball->y) ) { remove_block(ball->x+ball->width, ball->y, ball); }
      if ( hit(ball->x, ball->y+ball->height) ) { remove_block(ball->x, ball->y+ball->height, ball); }
      if ( hit(ball->x+ball->width, ball->y+ball->height) ) { remove_block(ball->x+ball->width, ball->y+ball->height, ball); }

      if ( num_blocks <= 0 ) {
        game_set_state(CLEAR);
      }
      break;

    case CLEAR:
      break;

    case DEAD:
      break;

    case RESTART:
      init_block();
      break;
  }
}
