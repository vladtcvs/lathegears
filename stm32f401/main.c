#define STM32F4

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/exti.h>

#include <stdio.h>
#include "common.h"
#include "control.h"
#include "interface.h"
#include "config.h"

#define FCPU 84000000UL
#define FTIMER 400000UL
#define PSC ((FCPU) / (FTIMER)-1)

void message(const char *msg)
{
}

static void blink(void)
{
    static bool val;
    if (val)
        gpio_clear(LED_PORT, LED_PIN);
    else
        gpio_set(LED_PORT, LED_PIN);

    val = !val;
}

static void make_step(void)
{
    gpio_clear(STEP_PORT, STEP_PIN);
}

static void clear_step(void)
{
    // set STEP pins not active (high) at the end of STEP
    // ______    _______
    //      |____|
    //
    //           ^
    //           |
    //           here
    gpio_set(STEP_PORT, STEP_PIN);
}

static void set_dir(bool dir)
{
    if (dir)
        gpio_set(DIR_PORT, DIR_PIN);
    else
        gpio_clear(DIR_PORT, DIR_PIN);
}

void tim2_isr(void)
{
    if (TIM_SR(TIM2) & TIM_SR_UIF)
    {
        TIM_SR(TIM2) &= ~TIM_SR_UIF;
        control_multiplyer_timer_tick();
        timer_set_counter(TIM2, 0);
    }
    else if (TIM_SR(TIM2) & TIM_SR_CC1IF)
    {
        TIM_SR(TIM2) &= ~TIM_SR_CC1IF;
        clear_step();
    }
}

void on_phase_A(void)
{
    int phase_B = !!gpio_get(PH_B_PORT, PH_B_PIN);

    if (phase_B)
        gpio_set(LED_PORT, LED_PIN);
    else
        gpio_clear(LED_PORT, LED_PIN);

    control_encoder_tick(phase_B);
}

void exti15_10_isr(void)
{
    /*uint32_t status = exti_get_flag_status(EXTI13); // phase A
    if (status)
    {
        on_phase_A();
    }*/
    exti_reset_request(EXTI10 | EXTI11 | EXTI12 | EXTI13 | EXTI14 | EXTI15);
}

void config_hw(void)
{
    rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

    /* Enable GPIOA,B,C clock. */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);

    /* Enable TIM2 clock for steps*/
    rcc_periph_clock_enable(RCC_TIM2);

    /* Enable EXTI */
    // EXTI is enabled

    // Delay
    int i;
    for (i = 0; i < 100000; i++)
        __asm__("nop");

    // Config LED
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, LED_PIN);
    gpio_set_output_options(LED_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, LED_PIN);
    gpio_set(LED_PORT, LED_PIN);

    // Config stepper pins
    gpio_set(STEP_PORT, STEP_PIN);
    gpio_mode_setup(STEP_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, STEP_PIN);
    gpio_set_output_options(STEP_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, STEP_PIN);

    gpio_set(DIR_PORT, DIR_PIN);
    gpio_mode_setup(DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, DIR_PIN);
    gpio_set_output_options(DIR_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, DIR_PIN);

    // Config encoder pins
    gpio_mode_setup(PH_A_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, PH_A_PIN);
    gpio_set(PH_A_PORT, PH_A_PIN);
    gpio_mode_setup(PH_B_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, PH_B_PIN);
    gpio_set(PH_B_PORT, PH_B_PIN);

    // Config interrupt on PB13 (phase A)
    exti_enable_request(EXTI13);
    exti_select_source(EXTI13, GPIOB);
    exti_set_trigger(EXTI13, EXTI_TRIGGER_RISING);

    // Config timer
    rcc_periph_reset_pulse(RST_TIM2);

    timer_set_prescaler(TIM2, PSC);
    timer_direction_up(TIM2);
    timer_disable_preload(TIM2);
    timer_update_on_overflow(TIM2);
    timer_enable_update_event(TIM2);
    timer_continuous_mode(TIM2);

    timer_set_oc_fast_mode(TIM2, TIM_OC1);
    timer_set_oc_value(TIM2, TIM_OC1, 1);

    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);

    nvic_enable_irq(NVIC_TIM2_IRQ);
    timer_enable_irq(TIM2, TIM_DIER_UIE);
    timer_enable_irq(TIM2, TIM_DIER_CC1IE);

    nvic_set_priority(NVIC_TIM2_IRQ, 6 * 16);
}

void start_timer(void)
{
    timer_set_counter(TIM2, 0);
    timer_set_period(TIM2, 4);
    timer_enable_counter(TIM2);
}

void stop_timer(void)
{
    timer_disable_counter(TIM2);
}

int main(void)
{
    config_hw();

    control_init(SPINDEL_ENCODER_STEPS, SCREW_STEPS, SCREW_PITCH, false, set_dir, make_step, start_timer, stop_timer, 64, 100000 / 5);
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

    control_select_thread(11);
    control_start_thread();

    bool oldPA = gpio_get(PH_A_PORT, PH_A_PIN);
    while (true)
    {
        bool PA = gpio_get(PH_A_PORT, PH_A_PIN);
        if (PA && (!oldPA))
            on_phase_A();
        oldPA = PA;
    }

    return 0;
}
