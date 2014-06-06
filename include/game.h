enum state { START, RUNNING, CLEAR, REMAINING, DEAD, RESTART };

extern void game_step(void);
extern enum state game_get_state(void);
extern void game_set_state(enum state);
