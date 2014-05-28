#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"
#include "utils.h"

static struct box block = { 10, 10, 25, 10 };

void block_step(void)
{
  switch ( game_get_state() ) {
    case START:
      break;

    case RUNNING:
      draw_box(&block, 15, 15, COLOR_WHITE);
      break;
  }
}
