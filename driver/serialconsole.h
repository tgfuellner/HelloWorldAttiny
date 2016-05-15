#ifndef __SERIALCONSOLE_H_
#define __SERIALCONSOLE_H_

#include <stdint.h>

// Provides a console through serial port.
// stdin and stdout are connected to the serial port.
// Input is buffered, output is not buffered.

// Required setting, usually in the Makefile:
// #define F_CPU 20000000

// Serial bitrate
#define SERIAL_BITRATE 4800     // Im Endeffekt dann 2400??!!

// Select one or more serial ports on ATtiny or ATmega controllers:
#define USE_SERIAL0
// #define USE_SERIAL1
// #define USE_SERIAL2
// #define USE_SERIAL3

// Select one or more serial ports on Xmega controllers:
// #define USE_USARTC0
// #define USE_USARTD0
// #define USE_USARTE0
// #define USE_USARTF0
// #define USE_USARTC1
// #define USE_USARTD1
// #define USE_USARTE1
// #define USE_USARTF1

// If you select more than one single serial port, then all ports send the
// same data and receive into the same shared buffer.

// In the software, lines are always terminated with \n.
// If terminal mode is enabled, line breaks are converted automatically:
// - in sending direction, line breaks are sent as \r\n.
// - in receiving direction, line breaks may be terminated by \r, \n or \r\n.
// - backspace characters in receiving direction delete the last received character from the input buffer.
#define TERMINAL_MODE 1

// Enable echo on serial interface
#define SERIAL_ECHO 0

// Size of input buffer in chars, max 254 (output is not buffered).
// Change it carefully, you get a stack overflow if the buffer occupies too much RAM.
#define SERIAL_INPUT_BUFFER_SIZE 40

// Initialize the serial port and bind it to stdin and stdout.
void initSerialConsole(void);

// Returns 1 if the serial port has received at least one character
// so that the following call to getc() does not block.
uint8_t receivedChar(void);

// Returns 1 if the serial port has received a line break
// so that the following call to gets() and scanf() does not block.
uint8_t receivedLine(void);

#endif //__SERIALCONSOLE_H_
