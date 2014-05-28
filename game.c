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
      draw_string("PRESS START KEY TO START.", 23, 85, COLOR_WHITE);
      if ( get_key_state(KEY_START) ) {
        draw_string("PRESS START KEY TO START.", 23, 85, COLOR_BLACK);
        game_set_state(RUNNING);
      }
      break;

    case RUNNING:
      // for Debug
      if ( get_key_state(KEY_SELECT) ) {
        game_set_state(CLEAR);
      }
      break;

    case DEAD:
      draw_string("GAME OVER", 85, 70, COLOR_WHITE);
      draw_string("PRESS START KEY TO RESTART.", 16, 85, COLOR_WHITE);
      if ( get_key_state(KEY_START) ) {
        init_screen();
        game_set_state(RESTART);
      }
      break;

    case CLEAR:
      draw_string("CLEAR", 100, 70, COLOR_WHITE);
      draw_string("PRESS START KEY TO RESTART.", 16, 85, COLOR_WHITE);
      if ( get_key_state(KEY_START) ) {
        init_screen();
        game_set_state(START);
      }
      break;

    case RESTART:
      game_set_state(RUNNING);
      break;
  }
}
