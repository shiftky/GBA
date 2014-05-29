#include "gba.h"
#include "delay.h"
#include "ball.h"
#include "racket.h"

#define INTERVAL 200

int main(void)
{
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
  gba_register(TMR_COUNT0) = 0;
  gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;

  while (1) {
    ball_step();
    racket_step();
    block_step();
    game_step();
    delay(INTERVAL);
  }

  return 0;
}
