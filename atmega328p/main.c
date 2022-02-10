#include <stdio.h>
#include "common.h"
#include "control.h"
#include "interface.h"
#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void message(const char *msg)
{
}

void blink(void)
{
    static bool val;
    if (val)
        LED_PORT |= 1 << LED_PIN;
    else
        LED_PORT &= ~(1 << LED_PIN);
    val = !val;
}

void make_step(void)
{
    blink();
    STEP_PORT &= ~(1 << STEP_PIN);
}

void set_dir(bool dir)
{
    if (dir)
        DIR_PORT |= (1 << DIR_PIN);
    else
        DIR_PORT &= ~(1 << DIR_PIN);    
}

ISR(TIMER0_COMPA_vect)
{
    control_multiplyer_timer_tick();
}

ISR(TIMER0_COMPB_vect)
{
    STEP_PORT |= 1 << STEP_PIN;
}

ISR(INT0_vect)
{
    int B = PH_B_PORT & (1 << PH_B_PIN);

    B = !!B;
    control_encoder_tick(B);
}

ISR(PCINT0_vect)
{

}

ISR(PCINT1_vect)
{
    
}

ISR(PCINT2_vect)
{
    
}

void config_hw(void)
{
    // Config LED
    LED_DDR |= 1 << LED_PIN;

    // Config stepper pins
    STEP_DDR |= 1 << STEP_PIN;
    DIR_DDR  |= 1 << DIR_PIN;

    // Config encoder pins
    PH_A_DDR &= ~(1 << PH_A_PIN);
    PH_B_DDR &= ~(1 << PH_B_PIN);

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

void start_timer(void)
{
    cli();
    TCCR0B |= ((0 << CS02) | (1 << CS01) | (0 < CS00));
    TCNT0 = 0;
    sei();
}

void stop_timer(void)
{
    cli();
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 < CS00));
    TCNT0 = 0;
    sei();
}

int main(void)
{
    config_hw();

    control_init(SPINDEL_ENCODER_STEPS, SCREW_STEPS, SCREW_PITCH, false, set_dir, make_step, start_timer, stop_timer);
    interface_init();

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

    while (true)
        ;

    return 0;
}

