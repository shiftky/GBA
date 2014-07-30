#include "gba.h"
#include "game.h"
#include "ball.h"
#include "block.h"
#include "racket.h"
#include "utils.h"
#include "debug.h"

#define INTERVAL 100

int main(void)
{
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
  gba_register(TMR_COUNT0) = 0;
  gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;

  while (1) {
    wait_until_vblank();
    ball_step();
    racket_step();
    block_step();
    game_step();
    delay(INTERVAL);
    wait_while_vblank();
  }

  return 0;
}
