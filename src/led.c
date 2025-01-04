#include "led.h"

int mode = FIRST_MODE;

static int first_delay = NULL;
static int second_delay = NULL;
static int third_delay = NULL;

static int speeds_second_mode[] = {
    50,
    25,
    100
};

static int current_speed = 0;

void LEDs_Init(void) {
    GPIO_InitLEDs();
    TIM_PWMTIMsInit();

    GPIO_SetFirstMode();

    first_delay = Delay_AddFunction(GPIO_ToggleFirstBlinkingLED, 50);
    second_delay = Delay_AddFunction(GPIO_ToggleSecondBlinkingLED, 100);
    third_delay = Delay_AddFunction(TIMs_PWM_ChangeDutyCicle, 1);
}

void LEDs_ToggleMode(void) {
    switch (mode)
    {
    case FIRST_MODE:
        GPIO_SetSecondMode();
        Delay_ChangeFunction(GPIO_LightNextLEDInChain, 50, first_delay);
        Delay_ToggleFunction(second_delay, FALSE);
        Delay_ToggleFunction(third_delay, FALSE);

        mode = SECOND_MODE;
        break;
    
    case SECOND_MODE:
        GPIO_SetFirstMode();
        Delay_ChangeFunction(GPIO_ToggleFirstBlinkingLED, 50, first_delay);
        Delay_ToggleFunction(second_delay, TRUE);
        Delay_ToggleFunction(third_delay, TRUE);

        mode = FIRST_MODE;
        break;
    }
}

void LEDs_Switch(void) {
    switch (mode)
    {
    case FIRST_MODE:
        GPIO_SwitchLEDsFirstMode();
        Change_PWM_TIMs();
        break;
    
    case SECOND_MODE:
        Delay_ChangeFunction(GPIO_LightNextLEDInChain, speeds_second_mode[(++current_speed) % SPEEDS_COUNT], first_delay);
        break;
    }
}
