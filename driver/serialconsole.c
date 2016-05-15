#include "serialconsole.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h> 


// Files for input and output through serial port.
static int serial_write(char, FILE *);
static int serial_read(FILE *);
static FILE serialPort = FDEV_SETUP_STREAM(serial_write, serial_read, _FDEV_SETUP_RW);

// input ring buffer
static volatile char inputBuffer[SERIAL_INPUT_BUFFER_SIZE];

// index of first character in the buffer
static volatile uint8_t inputStart=0;

// point to the next free position in the input buffer (=inputStart in case of empty buffer)
static volatile uint8_t inputEnd=0;

// The previously received character
static volatile char prevChar=0;

// Check if the serial port has received at least one character
uint8_t receivedChar(void) 
{
    return inputStart!=inputEnd;
}

// Check if the serial port has received a line break
uint8_t receivedLine(void) 
{
    int i=inputStart;
    while (i!=inputEnd) 
    {
        if (inputBuffer[i]=='\n') 
        {
            return 1;
        }
        if (++i>=SERIAL_INPUT_BUFFER_SIZE) 
        {
            i=0;
        }
    }
    return 0;
}

// Read a character from serial port
static int serial_read(FILE *f) 
{
    // wait until something is received
    while (inputStart==inputEnd);         
    char c=inputBuffer[inputStart];
    if (++inputStart>=SERIAL_INPUT_BUFFER_SIZE) 
    {
        inputStart=0;
    }
    return c;        
}

#if defined(__AVR_XMEGA__)
  #include "serialconsole_xmega.c"
#else
  #include "serialconsole_atmega.c"
#endif

