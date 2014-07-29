#ifndef _GAME_H
#define _GAME_H
enum state { START, NEXTSTAGE, RUNNING, CLEAR, REMAINING, DEAD, RESTART };

extern void game_step(void);
extern enum state game_get_state(void);
extern void game_set_state(enum state);
#endif
