enum state { START, RUNNING, DEAD, RESTART, CLEAR };

extern void game_step(void);
extern enum state game_get_state(void);
extern void game_set_state(enum state);
