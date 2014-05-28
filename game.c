#include "gba.h"
#include "game.h"
#include "utils.h"

static enum state current_state;

enum state game_get_state(void) { return current_state; }
void game_set_state(enum state new_state) { current_state = new_state; }

void game_step(void)
{
  switch ( game_get_state() ) {
    case START:
      draw_string("IMAGINE THE FUTURE.", 45, 30, COLOR_WHITE);
      break;

    case RUNNING:
      break;

    case DEAD:
      draw_string("GAME OVER", 85, 50, COLOR_WHITE);
      break;

    case CLEAR:
      draw_string("CLEAR", 100, 50, COLOR_WHITE);
      break;

    case RESTART:
      break;
  }
}
