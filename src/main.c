#include "stm32f767xx.h"

#include "timers.h"
#include "usart.h"
#include "buttons.h"
#include "gpio.h"
#include "led.h"

// PA0 - TIM5_CH1
// PE9 - TIM1_CH1
// PA3 - TIM5_CH4
// PE11 - TIM1_CH2

void __libc_init_array(void) {

}

int main() {
    USART3_GPIO_Init();
    USART3_Init();

    TIM_DelayTIMInit();

    Button_Init();

    LEDs_Init();

    while(1) {

    }
}

void ButtonClicked(void) {
    LEDs_Switch();
}

void ButtonDoubleClicked(void) {
    LEDs_ToggleMode();
}

void ButtonLongPressed(void) {

}
