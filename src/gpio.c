#include "gpio.h"

#define SLOW_PWM_INDEX (first_mode_index % GPIO_COUNT)
#define FAST_PWM_INDEX ((first_mode_index + 1) % GPIO_COUNT)
#define SLOW_BLINKING_INDEX ((first_mode_index + 2) % GPIO_COUNT)
#define FAST_BLINKING_INDEX ((first_mode_index + 3) % GPIO_COUNT)

#define CURRENT_BLINKING_INDEX (second_mode_index % GPIO_COUNT)
#define NEXT_BLINKING_INDEX ((second_mode_index + 1) % GPIO_COUNT)

#define INCREMENT_INDEX(index) (index = (index + 1) % GPIO_COUNT)

static int first_mode_index = 0;
static int second_mode_index = 0;

struct GPIOInitInfo {
    void (*init_as_gpio)(void);
    void (*init_as_pwm)(void);
    void (*toggler)(int);
};

static void PA0_Init_AsGPIO(void) {
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->MODER |= GPIO_MODER_MODER0_0;

    GPIOA->AFR[0] &= ~(0xf << GPIO_AFRL_AFRL0_Pos);
}

static void PE9_Init_AsGPIO(void) {
    GPIOE->MODER &= ~GPIO_MODER_MODER9;
    GPIOE->MODER |= GPIO_MODER_MODER9_0;

    GPIOE->AFR[1] &= ~(0xf << GPIO_AFRH_AFRH1_Pos);
}

static void PA3_Init_AsGPIO(void) {
    GPIOA->MODER &= ~GPIO_MODER_MODER3;
    GPIOA->MODER |= GPIO_MODER_MODER3_0;

    GPIOA->AFR[0] &= ~(0xf << GPIO_AFRL_AFRL3_Pos);
}

static void PE11_Init_AsGPIO(void) {
    GPIOE->MODER &= ~GPIO_MODER_MODER11;
    GPIOE->MODER |= GPIO_MODER_MODER11_0;

    GPIOE->AFR[1] &= ~(0xf << GPIO_AFRH_AFRH3_Pos);
}

static void PA0_Init_AsPWM(void) {
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->MODER |= GPIO_MODER_MODER0_1;

    GPIOA->AFR[0] |= (2 << GPIO_AFRL_AFRL0_Pos);
}

static void PE9_Init_AsPWM(void) {
    GPIOE->MODER &= ~GPIO_MODER_MODER9;
    GPIOE->MODER |= GPIO_MODER_MODER9_1;

    GPIOE->AFR[1] |= (1 << GPIO_AFRH_AFRH1_Pos);
}

static void PA3_Init_AsPWM(void) {
    GPIOA->MODER &= ~GPIO_MODER_MODER3;
    GPIOA->MODER |= GPIO_MODER_MODER3_1;

    GPIOA->AFR[0] |= (2 << GPIO_AFRL_AFRL3_Pos);
}

static void PE11_Init_AsPWM(void) {
    GPIOE->MODER &= ~GPIO_MODER_MODER11;
    GPIOE->MODER |= GPIO_MODER_MODER11_1;

    GPIOE->AFR[1] |= (1 << GPIO_AFRH_AFRH3_Pos);
}

static void PA0_Toggle(int val) {
    switch (val)
    {
    case TRUE:
        GPIOA->ODR |= GPIO_ODR_OD0;
        break;
    case FALSE:
        GPIOA->ODR &= ~GPIO_ODR_OD0;
        break;
    case NULL:
        GPIOA->ODR ^= GPIO_ODR_OD0;
        break;
    }
}

static void PE9_Toggle(int val) {
    switch (val)
    {
    case TRUE:
        GPIOE->ODR |= GPIO_ODR_OD9;
        break;
    case FALSE:
        GPIOE->ODR &= ~GPIO_ODR_OD9;
        break;
    case NULL:
        GPIOE->ODR ^= GPIO_ODR_OD9;
        break;
    }
}

static void PA3_Toggle(int val) {
    switch (val)
    {
    case TRUE:
        GPIOA->ODR |= GPIO_ODR_OD3;
        break;
    case FALSE:
        GPIOA->ODR &= ~GPIO_ODR_OD3;
        break;
    case NULL:
        GPIOA->ODR ^= GPIO_ODR_OD3;
        break;
    }
}

static void PE11_Toggle(int val) {
    switch (val)
    {
    case TRUE:
        GPIOE->ODR |= GPIO_ODR_OD11;
        break;
    case FALSE:
        GPIOE->ODR &= ~GPIO_ODR_OD11;
        break;
    case NULL:
        GPIOE->ODR ^= GPIO_ODR_OD11;
        break;
    }
}

// PA0 - TIM5_CH1
// PE9 - TIM1_CH1
// PA3 - TIM5_CH4
// PE11 - TIM1_CH2

static struct GPIOInitInfo init_info[] = {
    { &PA0_Init_AsGPIO, &PA0_Init_AsPWM, &PA0_Toggle },
    { &PE9_Init_AsGPIO, &PE9_Init_AsPWM, &PE9_Toggle },
    { &PA3_Init_AsGPIO, &PA3_Init_AsPWM, &PA3_Toggle },
    { &PE11_Init_AsGPIO, &PE11_Init_AsPWM, &PE11_Toggle },
};

void GPIO_SetFirstMode(void) {
    init_info[SLOW_PWM_INDEX].init_as_pwm();
    init_info[FAST_PWM_INDEX].init_as_pwm();
    init_info[SLOW_BLINKING_INDEX].init_as_gpio();
    init_info[FAST_BLINKING_INDEX].init_as_gpio();
}

void GPIO_SetSecondMode(void) {
    for (int i = 0; i < GPIO_COUNT; i++) {
        init_info[i].init_as_gpio();
        init_info[i].toggler(FALSE);
    }

    init_info[CURRENT_BLINKING_INDEX].toggler(TRUE);
}

void GPIO_SwitchLEDsFirstMode(void) {
    INCREMENT_INDEX(first_mode_index);
    GPIO_SetFirstMode();
}

void GPIO_SwitchLEDsSecondMode(void) {

}

void GPIO_LightNextLEDInChain(void) {
    init_info[CURRENT_BLINKING_INDEX].toggler(NULL);
    INCREMENT_INDEX(second_mode_index);
    init_info[CURRENT_BLINKING_INDEX].toggler(NULL);
}

void GPIO_ToggleFirstBlinkingLED(void) {
    init_info[SLOW_BLINKING_INDEX].toggler(NULL);
}

void GPIO_ToggleSecondBlinkingLED(void) {
    init_info[FAST_BLINKING_INDEX].toggler(NULL);
}

void GPIO_InitLEDs(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11;
}
