#include <stdio.h>
#include "common.h"
#include "control.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN 5 // PORTB

#define STEP_PIN 4
#define DIR_PIN 5

#define PH_A_PIN 2
#define PH_B_PIN 3

void message(const char *msg)
{
}

void blink(void)
{
    static bool val;
    if (val)
        PORTB |= 1 << LED_PIN;
    else
        PORTB &= ~(1 << LED_PIN);
    val = !val;
}

void make_step(void)
{
    blink();
    PORTD &= ~(1 << STEP_PIN);
}

void set_dir(bool dir)
{
    if (dir)
        PORTD |= (1 << DIR_PIN);
    else
        PORTD &= ~(1 << DIR_PIN);    
}

ISR(TIMER0_COMPA_vect)
{
    control_multiplyer_timer_tick();
}

ISR(TIMER0_COMPB_vect)
{
    PORTD |= 1 << STEP_PIN;
}

ISR(INT0_vect)
{
    int B = PIND & (1 << PH_B_PIN);

    B = !!B;
    control_encoder_tick(B);
}

void config_hw(void)
{
    // Config LED
    DDRB |= 1 << LED_PIN;

    // Config stepper pins
    DDRD |= 1 << STEP_PIN;
    DDRD |= 1 << DIR_PIN;

    // Config encoder pins
    DDRD &= ~(1 << PH_A_PIN);
    DDRD &= ~(1 << PH_B_PIN);

    // Config interrupt on INT0 (phase A)
    EIMSK  |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);

    // Config timer
    TCCR0A = (1 << WGM01) | (0 << WGM00);
    TCCR0B = (0 << WGM02) | (0 << CS02) | (0 << CS01) | (0 < CS00);
    TIMSK0 = (1 << OCIE0B) | (1 << OCIE0A);

    OCR0A = 64; // 16 MHz / 128 = 125 kHz
    OCR0B = 32;

    TCNT0 = 0;
}


void start_thread(int id)
{
    cli();
    control_select_thread(id);
    control_start_thread();
    TCCR0B |= ((0 << CS02) | (1 << CS01) | (0 < CS00));
    TCNT0 = 0;
    sei();
}

void stop_thread(void)
{
    cli();
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 < CS00));
    TCNT0 = 0;
    control_stop_thread();
    sei();
}


int main(void)
{
    config_hw();

    control_init(100, 200*2*3, 2.0, false, set_dir, make_step);

    control_register_thread(0.20, true); // 0
    control_register_thread(0.25, true); // 1
    control_register_thread(0.30, true); // 2
    control_register_thread(0.35, true); // 3
    control_register_thread(0.40, true); // 4
    control_register_thread(0.45, true); // 5
    control_register_thread(0.50, true); // 6
    control_register_thread(0.60, true); // 7
    control_register_thread(0.70, true); // 8
    control_register_thread(0.75, true); // 9
    control_register_thread(0.80, true); // 10
    control_register_thread(1.00, true); // 11
    control_register_thread(1.25, true); // 12
    control_register_thread(1.50, true); // 13
    control_register_thread(1.75, true); // 14
    control_register_thread(2.00, true); // 15
    control_register_thread(2.50, true); // 16
    control_register_thread(3.00, true); // 17

    sei();

    start_thread(11);

    while (true)
        ;

    return 0;
}

