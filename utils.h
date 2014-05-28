#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK BGR(0, 0, 0)

extern int get_key_state(int);
extern void draw_char(hword*, hword, int);
extern void draw_string(char*, int, int, hword);
extern void init_screen(void);
