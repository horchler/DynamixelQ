/*
 *	Timing.h
 *
 *	Author: Andrew D. Horchler, adh9 @ case.edu
 *	Created: 2-12-15, modified: 7-9-15
 */
 
#ifndef TIMING_H_
#define TIMING_H_
#if defined(__cplusplus)
extern "C" {
#endif

#include "stm32.h"
#include "systick.h"

#define US_PER_MS              1000
#define CYCLES_PER_MICROSECOND 72
#define SYSTICK_RELOAD_VAL     71999	/* takes a cycle to reload */

/*
 *	Returns time (in milliseconds) since the beginning of program execution. On overflow, restarts at 0.
 */
static inline unsigned long millisec(void)
{
    return systick_uptime();
}

/*
 *	Returns time (in microseconds) since the beginning of program execution. On overflow, restarts at 0.
 */
static inline unsigned long microsec(void)
{
    unsigned long ms, cycle_cnt;
	
    do {
        cycle_cnt = systick_get_count();
        ms = millisec();
    } while (ms != millisec());
	
    /* SYSTICK_RELOAD_VAL is 1 less than the number of cycles it actually takes to complete a SysTick reload */
    return (ms * US_PER_MS) + (SYSTICK_RELOAD_VAL + 1 - cycle_cnt) / CYCLES_PER_MICROSECOND;
}

// TODO: Write in ARM assembly in terms of clock cycles.
static void nsDelay(unsigned long ns)
{
	unsigned long i;
	static unsigned long cnt = 0;
	
	for (i = 0; i < ns; i++) {
		cnt += i;
	}
}

static inline void usDelay(unsigned long us)
{
    us *= STM32_DELAY_US_MULT;

    /* fudge for function call overhead */
    us--;
    asm volatile("   mov r0, %[us]          \n\t"
                 "1: subs r0, #1            \n\t"
                 "   bhi 1b                 \n\t"
                 :
                 : [us] "r" (us)
                 : "r0");
}

static void msDelay(unsigned long ms)
{
    unsigned long i;
	
    for (i = 0; i < ms; i++) {
		usDelay(US_PER_MS);
    }
}

static void secDelay(unsigned long sec)
{
    unsigned long i;
	
    for (i = 0; i < sec; i++) {
		msDelay(1000);
    }
}

static unsigned long usElapsed(void)
{
	unsigned long t_prv;
	static unsigned long t_now = 0;
	static int isInit = 1;
	
	if (isInit) {
		isInit = 0;
		t_now = microsec();
		
		return 0;
	} else {
		t_prv = t_now;
		t_now = microsec();
		
		return t_now - t_prv;
	}
}

static unsigned long msElapsed(void)
{
	unsigned long t_prv;
	static unsigned long t_now = 0;
	static int isInit = 1;
	
	if (isInit) {
		isInit = 0;
		t_now = millisec();
		
		return 0;
	} else {
		t_prv = t_now;
		t_now = millisec();
		
		return t_now - t_prv;
	}
}

#if defined(__cplusplus)
}
#endif

#endif /* TIMING_H_ */