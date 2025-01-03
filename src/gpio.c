#include "gpio.h"

static int gpio_info_index = 0;

struct GPIOInitInfo {
    void (*init_as_gpio)(void);
    void (*init_as_pwm)(void);
    void (*toggler)(void);
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

static void PA0_Toggle(void) {
    GPIOA->ODR ^= GPIO_ODR_OD0;
}

static void PE9_Toggle(void) {
    GPIOE->ODR ^= GPIO_ODR_OD9;
}

static void PA3_Toggle(void) {
    GPIOA->ODR ^= GPIO_ODR_OD3;
}

static void PE11_Toggle(void) {
    GPIOE->ODR ^= GPIO_ODR_OD11;
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

void Change_GPIOs(void) {
    int to_gpio_index = gpio_info_index % GPIO_COUNT; 
    int to_pwm_index = (gpio_info_index + 2) % GPIO_COUNT; 

    init_info[to_gpio_index].init_as_gpio();
    init_info[to_pwm_index].init_as_pwm();

    gpio_info_index = (gpio_info_index + 1) % GPIO_COUNT;
}

void Toggle_FirstBlinkingLED(void) {
    init_info[(gpio_info_index + 2) % GPIO_COUNT].toggler();
}

void Toggle_SecondBlinkingLED(void) {
    init_info[(gpio_info_index + 3) % GPIO_COUNT].toggler();
}

void GPIO_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11;

    init_info[0].init_as_pwm();
    init_info[1].init_as_pwm();
    init_info[2].init_as_gpio();
    init_info[3].init_as_gpio();
}
