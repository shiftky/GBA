#include "gba.h"
#include "ball.h"
#include "game.h"
#include "utils.h"

static enum state current_state;
static int current_stage;

enum state game_get_state(void) { return current_state; }
int game_get_stage(void) { return current_stage; }
void game_set_state(enum state new_state) { current_state = new_state; }

void game_step(void)
{
  switch ( game_get_state() ) {
    case START:
      current_stage = 0;
      draw_string("Press START key to start.", 23, 85, COLOR_WHITE);
      if ( get_key_state(KEY_START) ) {
        draw_string("Press START key to start.", 23, 85, COLOR_BLACK);
        game_set_state(REMAINING);
      }
      break;

    case NEXTSTAGE:
      game_set_state(REMAINING);
      break;

    case REMAINING:
      draw_string("stage ", 95, 75, COLOR_WHITE);
      draw_num(current_stage+1, 140, 75, COLOR_WHITE);
      draw_string("ball x", 90, 85, COLOR_WHITE);
      draw_num(ball_get_remaining(), 145, 85, COLOR_WHITE);
      delay(30000);
      draw_string("stage ", 95, 75, COLOR_BLACK);
      draw_num(current_stage+1, 140, 75, COLOR_BLACK);
      draw_string("ball x", 90, 85, COLOR_BLACK);
      draw_num(ball_get_remaining(), 145, 85, COLOR_BLACK);
      game_set_state(RUNNING);
      break;

    case RUNNING:
      // for Debug
      if ( get_key_state(KEY_SELECT) ) {
        game_set_state(CLEAR);
      }
      break;

    case DEAD:
      draw_string("GAME OVER", 85, 70, COLOR_RED);
      draw_string("Press START key to restart.", 16, 85, COLOR_WHITE);
      if ( get_key_state(KEY_START) ) {
        init_screen();
        game_set_state(RESTART);
      }
      break;

    case CLEAR:
      draw_string("CLEAR!!", 95, 70, COLOR_ITF);
      draw_string("Press A key to", 65, 85, COLOR_WHITE);
      draw_string("next stage!", 80, 95, COLOR_WHITE);
      if ( get_key_state(KEY_A) ) {
        init_screen();
        current_stage++;
        game_set_state(NEXTSTAGE);
      }
      break;

    case RESTART:
      game_set_state(START);
      break;
  }
}
