#include "buttons.h"
#include "usart.h"

#define BUTTON_PRESSED (GPIOC->IDR & GPIO_IDR_IDR_13)

#define TICKS_FOR_LONG_PRESS 100
#define TICKS_FOR_ONE_CLICK 10

#define NONE -1
#define BUTTON_CLICKED 0
#define BUTTON_DOUBLE_CLICKED 1
#define BUTTON_LONG_PRESSED 2

void Button_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER &= ~(GPIO_MODER_MODER13_0 | GPIO_MODER_MODER13_1);
    GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR13_1);
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR13_1;
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;

    Delay_AddFunction(Button_ClickManagerHandler, 1);
}

int Button_IsPressed(void) {
    return BUTTON_PRESSED;
}

void Button_ClickManagerHandler(void) {
    static int pressed_counter = 0;
    static int unpressed_counter = 0;
    static int was_pressed = FALSE;
    static int action = NONE;

    int is_pressed = BUTTON_PRESSED;

    is_pressed ? pressed_counter++ : unpressed_counter++;
    is_pressed ? (unpressed_counter = 0) : (pressed_counter = 0);

    if (was_pressed && !is_pressed) {
        switch (action)
        {
        case NONE:
            action = BUTTON_CLICKED;
            break;
        case BUTTON_CLICKED:
            action = BUTTON_DOUBLE_CLICKED;
            break;
        case BUTTON_LONG_PRESSED:
            action = NONE;
            break;
        }
    }

    if (is_pressed && (pressed_counter >= TICKS_FOR_LONG_PRESS) && (action != BUTTON_LONG_PRESSED)) {
        action = BUTTON_LONG_PRESSED;
        ButtonLongPressed();
    }

    if ((action != NONE) && (unpressed_counter >= TICKS_FOR_ONE_CLICK)) {
        switch(action)
        {
        case BUTTON_CLICKED:
            ButtonClicked();
            break;
        case BUTTON_DOUBLE_CLICKED:
            ButtonDoubleClicked();
            break;
        }
        action = NONE;
    }

    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
    }

    was_pressed = is_pressed;
}
