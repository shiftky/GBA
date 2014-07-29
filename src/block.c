#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
#include "utils.h"

#define BLOCK_COLS    8
#define BLOCK_ROWS    7
#define BLOCK_TOP     15
#define BLOCK_LEFT    20
#define BLOCK_WIDTH   25
#define BLOCK_HEIGHT  6
#define BALL_DY       1
#define BALL_DX       2

static struct box boxes[BLOCK_COLS][BLOCK_ROWS];
static char flags[BLOCK_COLS][BLOCK_ROWS];
static int num_blocks;
static int colors[BLOCK_ROWS] = { BGR(23,  8, 8),
                                  BGR(22, 12,  6),
                                  BGR(20, 14, 5),
                                  BGR(19, 19, 5),
                                  BGR(8,  19, 8),
                                  BGR(8, 15, 30),
                                  BGR(8, 8, 20) };

static int stages[2][BLOCK_ROWS][BLOCK_COLS] = {
  {
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 }
  },
  {
    {0, 0, 1, 1, 1, 1, 0, 0 },
    {0, 1, 1, 1, 1, 1, 1, 0 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 1, 1, 1, 1, 1, 1 },
    {0, 1, 1, 1, 1, 1, 1, 0 },
    {0, 0, 1, 1, 1, 1, 0, 0 }
  }
};

static void init_blocks(void)
{
  int i, j;

  num_blocks = 0;
  for ( i=0; i<BLOCK_COLS; i++ ) {
    for ( j=0; j<BLOCK_ROWS; j++ ) {
      if ( stages[game_get_stage()][j][i] ) {
        boxes[i][j].x = 20 + i*BLOCK_WIDTH;
        boxes[i][j].y = BLOCK_TOP + j*BLOCK_HEIGHT;
        boxes[i][j].width = BLOCK_WIDTH - 1;
        boxes[i][j].height = BLOCK_HEIGHT - 1;
        flags[i][j] = 1;
        num_blocks++;
        draw_box(&boxes[i][j], boxes[i][j].x, boxes[i][j].y, colors[j]);
      }
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
  int c = cross(&boxes[i][j], ball);

  if ( c >= 1 ) {
    flags[i][j] = 0;
    num_blocks--;
    draw_box(&boxes[i][j], boxes[i][j].x, boxes[i][j].y, COLOR_BLACK);
    if ( c == 2 || c == 3 ) {
      ball_set_dx( ball_get_dx() < 0 ? BALL_DX : -1 * BALL_DX );
    } else {
      ball_set_dy( ball_get_dy() < 0 ? BALL_DY : -1 * BALL_DY );
    }
  }
}

void block_step(void)
{
  struct box *ball;
  switch ( game_get_state() ) {
    case START:
      init_blocks();
      break;

    case NEXTSTAGE:
      init_blocks();
      break;

    case REMAINING:
      break;

    case RUNNING:
      ball = ball_get_box();
      if ( hit(ball->x, ball->y) == 1 ) { remove_block(ball->x, ball->y, ball); }
      if ( hit(ball->x+ball->width, ball->y) == 1 ) { remove_block(ball->x+ball->width, ball->y, ball); }
      if ( hit(ball->x, ball->y+ball->height) == 1 ) { remove_block(ball->x, ball->y+ball->height, ball); }
      if ( hit(ball->x+ball->width, ball->y+ball->height) == 1 ) { remove_block(ball->x+ball->width, ball->y+ball->height, ball); }

      if ( num_blocks <= 0 ) {
        game_set_state(CLEAR);
      }
      break;

    case CLEAR:
      break;

    case DEAD:
      break;

    case RESTART:
      init_blocks();
      break;
  }
}
