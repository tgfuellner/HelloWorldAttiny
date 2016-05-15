#include <avr/io.h>
#include <avr/interrupt.h>
#include "systemtimer.h"


// Incremented in each timer interrupt.
static volatile timer_t timerCounter;

    
// Return the current system timer value
timer_t milliseconds(void)
{
    timer_t tmp;
    cli();
    tmp=timerCounter;
    sei();
    return tmp;
}

    
//=======================================================   
// Timer initialisation routines for different AVR types
//=======================================================
    
#if defined(__AVR_ATtiny22__) || defined(__AVR_ATtiny26__) || defined(__AVR_ATmega8__) 
    void initSystemTimer(void)
    {
        cli();
        #if F_CPU>16000000
           TCCR0 = (1<<CS02); // Prescaler 256
           TCNT0 = 256-(F_CPU/256+500)/1000; 
        #elif F_CPU>2000000
           TCCR0 = (1<<CS01)+(1<<CS00); // Prescaler 64
           TCNT0 = 256-(F_CPU/64+500)/1000; 
        #else
           TCCR0 = (1<<CS01); // Prescaler 8
           TCNT0 = 256-(F_CPU/8+500)/1000; 
        #endif  
        TIMSK |= (1<<TOIE0); // Interrupt on overflow
        sei();
    }
    
#elif defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega162__) || defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__)
    void initSystemTimer(void)
    {
        cli();
        #if F_CPU>16000000
            TCCR0 = (1<<WGM01)+(1<<CS02)+(1<<CS00); // CTC Prescaler 128 
            OCR0 = (F_CPU/128+500)/1000;
        #elif F_CPU>8000000
            TCCR0 = (1<<WGM01)+(1<<CS02); // CTC Prescaler 64 
            OCR0 = (F_CPU/64+500)/1000;
        #elif F_CPU>2000000
            TCCR0 = (1<<WGM01)+(1<<CS01)+(1<<CS00); // CTC Prescaler 32
            OCR0 = (F_CPU/32+500)/1000;
        #else
            TCCR0 = (1<<WGM01)+(1<<CS01); // CTC Prescaler 8
            OCR0 = (F_CPU/8+500)/1000;
        #endif
        TIMSK |= (1<<OCIE0); // Interrupt on compare match
        sei();
    }
    
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
    void initSystemTimer(void)
    {
        cli();
        TCCR0A = (1<<WGM01); // CTC Mode
        #if F_CPU>16000000
           TCCR0B = (1<<CS02); // Prescaler 256
           OCR0A = (F_CPU/256+500)/1000; 
        #elif F_CPU>2000000
           TCCR0B = (1<<CS01)+(1<<CS00); // Prescaler 64
           OCR0A = (F_CPU/64+500)/1000; 
        #else
           TCCR0B = (1<<CS01); // Prescaler 8
           OCR0A = (F_CPU/8+500)/1000; 
        #endif  
        TIMSK |= (1<<OCIE0A); // Interrupt on compare match
        sei();
    }
    
#elif defined(__AVR_ATtiny261__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny861__)
    void initSystemTimer(void)
    {
        cli();
        TCCR0A = (1<<CTC0); // CTC Mode
        #if F_CPU>16000000
           TCCR0B = (1<<CS02); // Prescaler 256
           OCR0A = (F_CPU/256+500)/1000; 
        #elif F_CPU>2000000
           TCCR0B = (1<<CS01)+(1<<CS00); // Prescaler 64
           OCR0A = (F_CPU/64+500)/1000; 
        #else
           TCCR0B = (1<<CS01); // Prescaler 8
           OCR0A = (F_CPU/8+500)/1000; 
        #endif  
        TIMSK |= (1<<OCIE0A); // Interrupt on compare match
        sei();
    }

#elif defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny13A__) ||\
      defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || \
      defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || \
      defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || \
      defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || \
      defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) || \
      defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324P__) || \
      defined(__AVR_ATmega644__) || defined(__AVR_ATmega1284__) || \
      defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284P__) || \
      defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || \
      defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
    void initSystemTimer(void)
    {
        cli();
        TCCR0A = (1<<WGM01); // CTC Mode
        #if F_CPU>16000000
            TCCR0B = (1<<CS02); // Prescaler 256 
            OCR0A = (F_CPU/256+500)/1000;
        #elif F_CPU>2000000
            TCCR0B = (1<<CS01)+(1<<CS00); // Prescaler 64 
            OCR0A = (F_CPU/64+500)/1000;
        #else
            TCCR0B = (1<<CS01); // Prescaler 8
            OCR0A = (F_CPU/8+500)/1000;
        #endif 
        TIMSK0 |= (1<<OCIE0A); // Interrupt on compare match
        sei();
    }
    
#elif defined(PMIC) && defined(TCC0)
    // On Xmega, the calibrated R/C oscillator with 31.250Hz is used
    void initSystemTimer(void)
    {
        cli();
        PMIC.CTRL |= (1<<PIN0)+(1<<PIN1)+(1<<PIN2);
        TCC0.CNT = 0x00;
        TCC0.PER =  31250;
        TCC0.CTRLA = 0x01;
        TCC0.CTRLB = 0x00;
        TCC0.INTCTRLA = 0x03;
        sei();
    }

#else
    #error You need to edit driver/systemtimer.c to add code for your µC type
#endif

    
//=======================================================
// ISR routines for different AVR types
//=======================================================

#if defined(__AVR_ATtiny22__) || defined(__AVR_ATtiny26__) 
    ISR(TIMER0_OVF0_vect)
    {
        #if F_CPU>16000000
           TCNT0 = 256-(F_CPU/256+500)/1000; 
        #elif F_CPU>2000000
           TCNT0 = 256-(F_CPU/64+500)/1000; 
        #else
           TCNT0 = 256-(F_CPU/8+500)/1000; 
        #endif   
        timerCounter++;
    } 
  
#elif defined(__AVR_ATmega8__)
    ISR(TIMER0_OVF_vect)
    {
        #if F_CPU>16000000
           TCNT0 = 256-(F_CPU/256+500)/1000; 
        #elif F_CPU>2000000
           TCNT0 = 256-(F_CPU/64+500)/1000; 
        #else
           TCNT0 = 256-(F_CPU/8+500)/1000; 
        #endif   
        timerCounter++;
    } 

#elif defined(TIMER0_COMP_vect)
    ISR(TIMER0_COMP_vect)
    {
        timerCounter++;
    }    
    
#elif defined(TIMER0_COMPA_vect)
    ISR(TIMER0_COMPA_vect)
    {
        timerCounter++;
    }    
    
#elif defined(TIM0_COMPA_vect)
    ISR(TIM0_COMPA_vect)
    {
        timerCounter++;
    }
    
#elif defined(TCC0_OVF_vect)
    ISR(TCC0_OVF_vect)
    {
        timerCounter++;
    } 
    
#else
    #error You need to edit driver/systemtimer.c to add code for your µC type
#endif    
