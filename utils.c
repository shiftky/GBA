#include "gba.h"
#include "utils.h"
#include "8x8.til"

int get_key_state(int key_type)
{
  return !(gba_register(KEY_STATUS) & key_type);
}

void wait_until(hword time)
{
  while ( time != gba_register(TMR_COUNT0) );
}

void delay(hword val)
{
  wait_until(gba_register(TMR_COUNT0) + val);
}

void wait_until_vblank(void)
{
  while ( (gba_register(LCD_STATUS) & 1) == 0 );
}

void wait_while_vblank(void)
{
  while ( (gba_register(LCD_STATUS) & 1) );
}

void draw_char(hword *ptr, hword color, int code)
{
  hword *p;
  int i, j;
  unsigned char *font = char8x8[code];
  for ( i = 0; i < FONT_SIZE; i++ ) {
    p = ptr + LCD_WIDTH * i;
    for ( j = FONT_SIZE - 1; j >= 0; j--, p++ ) {
      if (font[i] & (1 << j)) {
        *p = color;
      }
    }
  }
}

void draw_num(int n, int x, int y, hword color)
{
  int i = 0, j, k;
  char num_str[LCD_WIDTH/8];
  while ( n > 10 ) {
    num_str[i] = n % 10 + 0x30;
    n = n / 10;
    i++;
  }
  num_str[i] = n + 0x30;
  for ( k=0, j=i; j>=0; j--, k++ ) {
    draw_char((hword*)VRAM + (LCD_WIDTH * y) + x+FONT_SIZE*k, color, num_str[j]);
  }
}

void draw_string(char *str, int x, int y, hword color)
{
  int i;
  for ( i=0; str[i] != '\0'; i++ ) {
    draw_char((hword*)VRAM + (LCD_WIDTH * y) + x+FONT_SIZE*i, color, str[i]);
  }
}

void init_screen(void)
{
  int i, j;
  hword* ptr = (hword*) VRAM;
  for ( i=0; i<LCD_WIDTH; i++ ) {
    for ( j=0; j<LCD_HEIGHT; j++ ) {
      *(ptr++) = COLOR_BLACK;
    }
  }
}
