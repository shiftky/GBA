#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
#include "utils.h"

static struct box block = { 100, 15, 25, 10 };

void block_step(void)
{
  switch ( game_get_state() ) {
    case START:
      break;

    case RUNNING:
      draw_box(&block, block.x, block.y, COLOR_WHITE);
      if ( cross( ball_get_box(), &block ) == 1 ) {
        draw_box(&block, block.x, block.y, COLOR_BLACK);
        game_set_state(CLEAR);
      }
      break;
  }
}
