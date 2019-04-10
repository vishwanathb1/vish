#include <avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
uint16_t ReadADC(uint8_t ch);
int main(void)
{
    TCCR0A |= ((1<<COM0A1) | (1<<WGM01) | (1<<WGM00));
    TCCR0B |= ((1<<CS00) | (1<<CS01));
    TCNT0 = 0X00;
    InitADC();
    uint16_t x = 0;
    DDRD |= (1<<6);
    // Insert code

    while(1)
    {
        x = ReadADC(0);
        if (x >= 0 && x <= 200)
        {
        OCR0A=20;
        _delay_ms(500);
        }
        if (x > 200  && x <= 400)
        {
        OCR0A=50;
        _delay_ms(500);
        }
        if (x > 400 && x <= 700)
        {
            OCR0A=100;
        _delay_ms(500);
        }
        if (x > 700 && x <= 900)
        {
            OCR0A=150;
        _delay_ms(500);
        }if (x > 900 && x <= 1024)
        {
            OCR0A=200;
        _delay_ms(500);
        }

        //DO NOTHING
    }

    return 0;
}
 void InitADC()
    {
        ADMUX = (1<<REFS0);
        ADCSRA = (1<<ADEN) | (7<<ADPS0);
    }
    uint16_t ReadADC(uint8_t ch)
    {
        ADMUX &= 0XF8;
        ch = ch & 0b00000111;
        ADMUX |= ch;
        ADCSRA |= (1<<ADSC);
        while(!(ADCSRA & (1<<ADIF)));
        ADCSRA |= (1<<ADIF);
        return ADC;
    }
