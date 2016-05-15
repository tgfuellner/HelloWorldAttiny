#ifndef _HARDWARE_H__
#define _HARDWARE_H__

#include <avr/io.h>

// This file defines macros for access to I/O pins.
// See also serial port settings in driver/serialconsole.h.

// The LED is connected to Port A1 and GND.
#define LED_ON  { DDRA |= (1<<PA1); PORTA |= (1<<PA1); }
#define LED_OFF { PORTA &= ~(1<<PA1);  }

#endif // _HARDWARE_H__
