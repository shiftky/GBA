#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
#include "utils.h"

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
  block.x = 50; block.y = 15;
  block.width = 25; block.height = 10;
  block2.x = 100; block2.y = 15;
  block2.width = 25; block2.height = 10;
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
