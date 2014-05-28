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
      draw_string("IMAGINE THE FUTURE.", 40, 20, COLOR_WHITE);
      if ( get_key_status(KEY_START) ) {
        draw_string("IMAGINE THE FUTURE.", 40, 20, COLOR_BLACK);
        game_set_state(RUNNING);
      }
      break;

    case RUNNING:
      break;

    case DEAD:
      draw_string("GAME OVER", 50, 50, COLOR_WHITE);
      if ( get_key_status(KEY_START) ) {
        draw_string("GAME OVER", 50, 50, COLOR_BLACK);
        game_set_state(START);
      }
      break;

    case RESTART:
      game_set_state(RUNNING);
      break;
  }
}
