void wait_until(hword time) { while ( time != gba_register(TMR_COUNT0) ); }
void delay(hword val) { wait_until(gba_register(TMR_COUNT0) + val); }
