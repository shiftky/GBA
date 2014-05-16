#include "gba.h"
#include "ball.h"
#include "racket.h"

void wait(int val) {
  int i, j;
  for (i = 0; i < val; i++)
    for (j = 0; j < val; j++)
  ;
}

void delay(hword val)
{
  val += gba_register(TMR_COUNT0);
  while (val != gba_register(TMR_COUNT0));
}

int main(void)
{
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
  gba_register(TMR_COUNT0) = 0;
  gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;

  while (1) {
    racket_step();
    ball_step();
    ball_step2();
    ball_step3();
    delay(200);
  }

  return 0;
}
