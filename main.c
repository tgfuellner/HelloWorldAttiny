#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <util/delay.h> 
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "driver/serialconsole.h"
#include "driver/systemtimer.h"
#include "hardware.h"


int main(void) 
{
    initSerialConsole();   
    initSystemTimer();
    
    while(1)
    {
         LED_ON;
        puts_P(PSTR("Hello World"));
        _delay_ms(500);    

        LED_OFF;
        char buffer[6];
        utoa(milliseconds(),buffer,10);
        puts(buffer);
        _delay_ms(100);
    }
}

