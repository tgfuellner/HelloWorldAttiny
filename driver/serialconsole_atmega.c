// included by serialconsole.c
// This file contains the parts that are specific for ATtiny and ATmega controllers.

#define BAUD SERIAL_BITRATE
#include <util/setbaud.h>

// Define aliases for ATtiny and ATmega controllers that have only one serial port
#ifndef UCSR0A
    #define UCSR0A UCSRA
    #define UCSR0B UCSRB
    #define UCSR0C UCSRC
    #define UBRR0H UBRRH
    #define UBRR0L UBRRL
    #define UDRE0  UDRE
    #define UDR0   UDR
    #define RXC0   RXC
    #define RXEN0  RXEN
    #define TXEN0  TXEN
    #define UCSZ00 UCSZ0
    #define UCSZ01 UCSZ1
    #define U2X0   U2X
    #define RXCIE0 RXCIE
    #define TXCIE0 TXCIE  
#endif 

#ifndef USART0_RX_vect
    #ifdef USART_RXC_vect
        #define USART0_RX_vect USART_RXC_vect
        #define USART0_TX_vect USART_TXC_vect
    #endif
    #ifdef USART_RX_vect
        #define USART0_RX_vect USART_RX_vect
        #define USART0_TX_vect USART_TX_vect
    #endif 
#endif

// Initialize the serial port
void initSerialConsole(void) 
{
    #ifdef USE_SERIAL0
        // set baudrate
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;
        #if USE_2X
            UCSR0A |= (1 << U2X0);
        #else
            UCSR0A &= ~(1 << U2X0);
        #endif
        // framing format 8N1
        #ifdef URSEL
            UCSR0C = (1<<URSEL) | (1<<UCSZ01) | (1<<UCSZ00);
        #else 
            UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
        #endif
        // enable receiver and transmitter
        UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1 << RXCIE0);
    #endif
    #ifdef USE_SERIAL1
        // set baudrate
        UBRR1H = UBRRH_VALUE;
        UBRR1L = UBRRL_VALUE;
        #if USE_2X
            UCSR1A |= (1 << U2X);
        #else
            UCSR1A &= ~(1 << U2X);
        #endif
        // framing format 8N1
        #ifdef URSEL
            UCSR1C = (1<<URSEL) | (1<<UCSZ11) | (1<<UCSZ10);
        #else 
            UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
        #endif
        // enable receiver and transmitter
        UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1 << RXCIE1);
    #endif  
    #ifdef USE_SERIAL2
        // set baudrate
        UBRR2H = UBRRH_VALUE;
        UBRR2L = UBRRL_VALUE;
        #if USE_2X
            UCSR2A |= (1 << U2X);
        #else
            UCSR2A &= ~(1 << U2X);
        #endif
        // framing format 8N1
        #ifdef URSEL
            UCSR2C = (1<<URSEL) | (1<<UCSZ21) | (1<<UCSZ20);
        #else 
            UCSR2C = (1<<UCSZ21) | (1<<UCSZ20);
        #endif
        // enable receiver and transmitter
        UCSR2B = (1<<RXEN2) | (1<<TXEN2) | (1 << RXCIE2);
    #endif      
    #ifdef USE_SERIAL3
        // set baudrate
        UBRR3H = UBRRH_VALUE;
        UBRR3L = UBRRL_VALUE;
        #if USE_2X
            UCSR3A |= (1 << U2X);
        #else
            UCSR3A &= ~(1 << U2X);
        #endif
        // framing format 8N1
        #ifdef URSEL
            UCSR3C = (1<<URSEL) | (1<<UCSZ31) | (1<<UCSZ30);
        #else 
            UCSR3C = (1<<UCSZ31) | (1<<UCSZ30);
        #endif
        // enable receiver and transmitter
        UCSR3B = (1<<RXEN3) | (1<<TXEN3) | (1 << RXCIE3);
    #endif  
    sei();
    // Bind stdout stdin to the serial port
    stdout = &serialPort;
    stdin = &serialPort;
    inputStart=0;
    inputEnd=0;
}

// Write a character to the serial port
static int serial_write(char c, FILE *f) 
{
    #if TERMINAL_MODE
        if (c=='\n') 
        {
            // wait until transmitter is ready
            #ifdef USE_SERIAL0
                loop_until_bit_is_set(UCSR0A, UDRE0);
                UDR0='\r';
            #endif
            #ifdef USE_SERIAL1
                loop_until_bit_is_set(UCSR1A, UDRE1);
                UDR1='\r';
            #endif 
            #ifdef USE_SERIAL2
                loop_until_bit_is_set(UCSR2A, UDRE2);
                UDR2='\r';
            #endif 
            #ifdef USE_SERIAL3
                loop_until_bit_is_set(UCSR3A, UDRE3);
                UDR3='\r';
            #endif                          
        }
    #endif
    // wait until transmitter is ready
    #ifdef USE_SERIAL0
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = c;
    #endif
    #ifdef USE_SERIAL1
        loop_until_bit_is_set(UCSR1A, UDRE1);
        UDR1 = c;
    #endif
    #ifdef USE_SERIAL2
        loop_until_bit_is_set(UCSR2A, UDRE2);
        UDR1 = c;
    #endif
    #ifdef USE_SERIAL3
        loop_until_bit_is_set(UCSR3A, UDRE3);
        UDR3 = c;
    #endif        
    return 0;
}

static void gotchar(char c) 
{
    #if TERMINAL_MODE
        // If received a backspace character, then discard the last 
        // received character
        if (c=='\b') 
        {
            if (inputStart!=inputEnd) 
            {
                if (--inputEnd<0) 
                {
                    inputEnd=0;
                }               
            }
            #if SERIAL_ECHO
                serial_write(c,0);
            #endif 
            return;
        }
        // If received a line feed and the previous character was a 
        // carriage-return (or vice versa) then ignore the new character
        if ((c=='\n' && prevChar=='\r') || (c=='\r' && prevChar=='\n')) 
        {
            return;
        }
        prevChar=c;
        // If received a carriage-return, then replace it by a line-feed
        if (c=='\r') 
        {
            c='\n';
        }
    #endif
    // Buffer the received character        
    inputBuffer[inputEnd]=c;
    if (++inputEnd>=SERIAL_INPUT_BUFFER_SIZE) 
    {
        inputEnd=0;
    }        
    // Discard oldest buffered character in case of buffer overflow
    if (inputEnd==inputStart) 
    {
        if (++inputStart>=SERIAL_INPUT_BUFFER_SIZE) 
        {
            inputStart=0;
        }
    }  
    #if SERIAL_ECHO
        serial_write(c,0);
    #endif 
} 

// USART Receive interrupt
#ifdef USE_SERIAL0
    ISR ( USART0_RX_vect ) 
    { 
        gotchar(UDR0);
    }
#endif

#ifdef USE_SERIAL1
    ISR ( USART1_RX_vect ) 
    { 
        gotchar(UDR1);
    }
#endif

#ifdef USE_SERIAL2
    ISR ( USART2_RX_vect ) 
    { 
        gotchar(UDR2);
    }
#endif

#ifdef USE_SERIAL3
    ISR ( USART3_RX_vect ) 
    { 
        gotchar(UDR3);
    }
#endif

