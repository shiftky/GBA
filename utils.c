#include "gba.h"
#include "utils.h"
#include "8x8.til"

#define FONT_SIZE 8
#define CHAR_SIZE 255

int get_key_status(int key_type) { return !(gba_register(KEY_STATUS) & key_type); }

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

void draw_string(char *str, int x, int y, hword color)
{
  int i;
  for ( i=0; str[i] != '\0'; i++ ) {
    draw_char((hword*)VRAM + (LCD_WIDTH * y) + x+FONT_SIZE*i, color, str[i]);
  }
}
