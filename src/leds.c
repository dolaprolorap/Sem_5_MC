#include "leds.h"

static struct LedInfo leds[] = {
    {GPIOD, 2},
    {GPIOD, 3},
    {GPIOD, 4},
    {GPIOD, 5},
};

static int led_index = 0;
static int current_status = FIRST_STATUS;

static inline void Leds_SetFirstStatus(void) {
    
}

static inline void Leds_SetSecondStatus(void) {
    
}

static inline void Leds_ShiftFirstStatus(void) {
    
}

static inline void Leds_ShiftSecondStatus(void) {
    
}

void Leds_Init(void) {
    TIM_PWM1_Init();
    GPIO_PWMLed1_Init();

    switch(current_status) {
        case FIRST_STATUS:
            break;
        case SECOND_STATUS:
            break;
    }
}

void Leds_SetStatus(int status) {
    switch(status) {
        case FIRST_STATUS:
            Leds_SetFirstStatus();
            break;
        case SECOND_STATUS:
            Leds_SetSecondStatus();
            break;
    }
}

void Leds_Shift(void) {
    switch(current_status) {
        case FIRST_STATUS:
            Leds_ShiftFirstStatus();
            break;
        case SECOND_STATUS:
            Leds_ShiftSecondStatus();
            break;
    }
}
