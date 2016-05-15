// included by serialconsole.c
// This file contains the parts that are specific for Xmega controllers.

// Initialize the serial port
void initSerialConsole(void) 
{
    int bsel=(int)(4*(((float)F_CPU/(16*(float)SERIAL_BITRATE))-1));
    PMIC.CTRL |= PMIC_HILVLEN_bm; // Enable high level interrupts
    #ifdef USE_USARTC0
        USARTC0.BAUDCTRLA = (uint8_t) bsel;
        USARTC0.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTC0.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTC0.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTC0.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver  
        PORTC.OUTSET = (1<<3); // TxD Pin is output
        PORTC.DIRSET = (1<<3); 
    #endif
    #ifdef USE_USARTD0
        USARTD0.BAUDCTRLA = (uint8_t) bsel;
        USARTD0.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTD0.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTD0.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTD0.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver  	
        PORTD.OUTSET = (1<<3); // TxD Pin is output
        PORTD.DIRSET = (1<<3); 
    #endif
    #ifdef USE_USARTE0
        USARTE0.BAUDCTRLA = (uint8_t) bsel;
        USARTE0.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTE0.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTE0.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTE0.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver  	
        PORTE.OUTSET = (1<<3); // TxD Pin is output
        PORTE.DIRSET = (1<<3); 
    #endif
    #ifdef USE_USARTF0
        USARTF0.BAUDCTRLA = (uint8_t) bsel;
        USARTF0.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTF0.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTF0.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTF0.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver  	
        PORTF.OUTSET = (1<<3); // TxD Pin is output
        PORTF.DIRSET = (1<<3);
    #endif 
    #ifdef USE_USARTC1
        USARTC1.BAUDCTRLA = (uint8_t) bsel;
        USARTC1.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTC1.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTC1.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTC1.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver  	
        PORTC.OUTSET = (1<<7); // TxD Pin is output
        PORTC.DIRSET = (1<<7);
    #endif
    #ifdef USE_USARTD1
        USARTD1.BAUDCTRLA = (uint8_t) bsel;
        USARTD1.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTD1.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTD1.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTD1.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver  	
        PORTD.OUTSET = (1<<7); // TxD Pin is output
        PORTD.DIRSET = (1<<7);
    #endif
    #ifdef USE_USARTE1
        USARTE1.BAUDCTRLA = (uint8_t) bsel;
        USARTE1.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTE1.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTE1.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTE1.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver
        PORTE.OUTSET = (1<<7); // TxD Pin is output
        PORTE.DIRSET = (1<<7);
    #endif
    #ifdef USE_USARTF1
        USARTF1.BAUDCTRLA = (uint8_t) bsel;
        USARTF1.BAUDCTRLB = (-2<<4) | (bsel >> 8); // BSCALE = -2
        USARTF1.CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc; // async, no parity, 8 bit data, 1 stop bit     
        USARTF1.CTRLA = USART_RXCINTLVL_HI_gc; // receive interrupts enable         
        USARTF1.CTRLB = USART_TXEN_bm | USART_RXEN_bm; // Enable transmitter and receiver 
        PORTF.OUTSET = (1<<7); // TxD Pin is output
        PORTF.DIRSET = (1<<7);
    #endif        
    sei(); 
    // Bind stdout and stdin to the serial port
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
            #ifdef USE_USARTC0
                loop_until_bit_is_set(USARTC0.STATUS,USART_DREIF_bp); 
                USARTC0.DATA='\r';
            #endif
            #ifdef USE_USARTD0
                loop_until_bit_is_set(USARTD0.STATUS,USART_DREIF_bp); 
                USARTD0.DATA='\r';
            #endif
            #ifdef USE_USARTE0
                loop_until_bit_is_set(USARTE0.STATUS,USART_DREIF_bp); 
                USARTE0.DATA='\r';
            #endif
            #ifdef USE_USARTF0
                loop_until_bit_is_set(USARTF0.STATUS,USART_DREIF_bp); 
                USARTF0.DATA='\r';
            #endif
            #ifdef USE_USARTC1
                loop_until_bit_is_set(USARTC1.STATUS,USART_DREIF_bp); 
                USARTC1.DATA='\r';
            #endif
            #ifdef USE_USARTD1
                loop_until_bit_is_set(USARTD1.STATUS,USART_DREIF_bp); 
                USARTD1.DATA='\r';
            #endif
            #ifdef USE_USARTE1
                loop_until_bit_is_set(USARTE1.STATUS,USART_DREIF_bp); 
                USARTE1.DATA='\r';
            #endif
            #ifdef USE_USARTF1
                loop_until_bit_is_set(USARTF1.STATUS,USART_DREIF_bp); 
                USARTF1.DATA='\r';
            #endif
        }
    #endif
    // wait until transmitter is ready
    #ifdef USE_USARTC0
        loop_until_bit_is_set(USARTC0.STATUS,USART_DREIF_bp); 
        USARTC0.DATA = c;  
    #endif
    #ifdef USE_USARTD0
        loop_until_bit_is_set(USARTD0.STATUS,USART_DREIF_bp); 
        USARTD0.DATA = c;  
    #endif
    #ifdef USE_USARTE0
        loop_until_bit_is_set(USARTE0.STATUS,USART_DREIF_bp); 
        USARTE0.DATA = c;  
    #endif
    #ifdef USE_USARTF0
        loop_until_bit_is_set(USARTF0.STATUS,USART_DREIF_bp); 
        USARTF0.DATA = c;  
    #endif
    #ifdef USE_USARTC1
        loop_until_bit_is_set(USARTC1.STATUS,USART_DREIF_bp); 
        USARTC1.DATA = c;  
    #endif
    #ifdef USE_USARTD1
        loop_until_bit_is_set(USARTD1.STATUS,USART_DREIF_bp); 
        USARTD1.DATA = c;  
    #endif
    #ifdef USE_USARTE1
        loop_until_bit_is_set(USARTE1.STATUS,USART_DREIF_bp); 
        USARTE1.DATA = c;  
    #endif
    #ifdef USE_USARTF1
        loop_until_bit_is_set(USARTF1.STATUS,USART_DREIF_bp); 
        USARTF1.DATA = c;  
    #endif    
    return 0;
}

static void gotchar(char c) 
{
    #if TERMINAL_MODE
        // If received a backspace character, then discard the last received character
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

// Receive interrupt
#ifdef USE_USARTC0
    ISR(USARTC0_RXC_vect) 
    {
        gotchar(USARTC0.DATA);
    }
#endif

#ifdef USE_USARTD0
    ISR(USARTD0_RXC_vect) 
    {
        gotchar(USARTD0.DATA);
    }
#endif

#ifdef USE_USARTE0
    ISR(USARTE0_RXC_vect) 
    {
        gotchar(USARTE0.DATA);
    }
#endif

#ifdef USE_USARTF0
    ISR(USARTF0_RXC_vect) 
    {
        gotchar(USARTF0.DATA);
    }
#endif

#ifdef USE_USARTC1
    ISR(USARTC1_RXC_vect) 
    {
        gotchar(USARTC1.DATA);
    }
#endif

#ifdef USE_USARTD1
    ISR(USARTD1_RXC_vect) 
    {
        gotchar(USARTD1.DATA);
    }
#endif

#ifdef USE_USARTE1
    ISR(USARTE1_RXC_vect) 
    {
        gotchar(USARTE1.DATA);
    }
#endif

#ifdef USE_USARTF1
    ISR(USARTF1_RXC_vect) 
    {
        gotchar(USARTF1.DATA);
    }
#endif

