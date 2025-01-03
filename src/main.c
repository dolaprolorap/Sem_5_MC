#include "stm32f767xx.h"

#include "timers.h"
#include "usart.h"
#include "buttons.h"
#include "gpio.h"
#include "leds.h"

// PA0 - TIM5_CH1
// PE9 - TIM1_CH1
// PA3 - TIM5_CH4
// PE11 - TIM1_CH2

void __libc_init_array(void) {

}

int main() {
    USART3_GPIO_Init();
    USART3_Init();

    Button_Init();
    Leds_Init();

    TIMs_Init();

    while(1) {

    }
}

void ButtonClicked(void) {
    Change_PWM_TIMs();
    USART3_SendString("Single click\n\r");
}

void ButtonDoubleClicked(void) {
    USART3_SendString("Double click\n\r");
}

void ButtonLongPressed(void) {
    USART3_SendString("Long press\n\r");
}
