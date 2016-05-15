#ifndef SYSTEMTIMER_H
#define	SYSTEMTIMER_H

// Uses timer 0 to count milliseconds.

// To get exact milliseconds, use one of the following crystals:
// 2.048MHz, 4.032MHz, 5.120MHz, 6.144MHz, 6.400MHz, 8.000MHz
// 9.216MHz, 10.240MHz, 12.288MHz, 16.000MHz
// Otherwise the intervals would be a little more or less than 1ms.

// Size of the timer counter. You may change this to 32bit, if needed.
#define timer_t uint16_t

// Return the current count of milliseconds.
timer_t milliseconds(void);

// Call this function to start timer 0.
void initSystemTimer(void);

#endif	/* SYSTEMTIMER_H */

