#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
#include "utils.h"

#define BLOCK_COLS    8
#define BLOCK_ROWS    5
#define BLOCK_TOP     10
#define BLOCK_WIDTH   25
#define BLOCK_HEIGHT  10

static struct box boxes[BLOCK_COLS][BLOCK_ROWS];
static char flags[BLOCK_COLS][BLOCK_ROWS];
static int num_blocks;

static struct box block = { 50, 15, 25, 10 };
static struct box block2 = { 100, 15, 25, 10 };
static int box_cnt = 2;

void delete_block(struct box *block)
{
  draw_box(block, block->x, block->y, COLOR_BLACK);
  block->x = block->y = block->width = block->height = 0;
}

void init_block(void)
{
  int i, j;
  num_blocks = BLOCK_COLS * BLOCK_ROWS;
  for ( i=0; i<BLOCK_COLS; i++ ) {
    for ( j=0; j<BLOCK_ROWS; j++ ) {
      boxes[i][j].x = i*BLOCK_WIDTH + 20;
      boxes[i][j].y = BLOCK_TOP + j*BLOCK_HEIGHT;
      boxes[i][j].width = BLOCK_WIDTH - 1;
      boxes[i][j].height = BLOCK_HEIGHT - 1;
      flags[i][j] = 1;
      draw_box(&boxes[i][j], boxes[i][j].x, boxes[i][j].y, COLOR_WHITE);
    }
  }
}

void block_step(void)
{
  switch ( game_get_state() ) {
    case START:
      init_block();
      break;

    case RUNNING:
      draw_box(&block, block.x, block.y, COLOR_WHITE);
      draw_box(&block2, block2.x, block2.y, COLOR_WHITE);

      if ( cross( ball_get_box(), &block ) == 1 ) {
        delete_block(&block);
        ball_set_dy(-1 * ball_get_dy());
        box_cnt--;
      }
      if ( cross( ball_get_box(), &block2 ) == 1 ) {
        delete_block(&block2);
        ball_set_dy(-1 * ball_get_dy());
        box_cnt--;
      }

      if ( box_cnt <= 0 ) {
        game_set_state(CLEAR);
      }
      break;
  }
}
