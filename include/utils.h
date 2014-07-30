#ifndef _UTILS_H
#define _UTILS_H

#define COLOR_YELLOW BGR(31, 31, 0)
#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK BGR(0, 0, 0)
#define COLOR_RED BGR(31, 0, 0)
#define COLOR_ITF BGR(3, 21, 25)
#define FONT_SIZE 8
#define CHAR_SIZE 255

extern int get_key_state(int);
extern void wait_until(hword);
extern void delay(hword);
extern void wait_until_vblank(void);
extern void wait_while_vblank(void);
extern void draw_char(hword*, hword, int);
extern void draw_num(int, int, int, hword);
extern void draw_string(char*, int, int, hword);
extern void init_screen(void);
#endif
