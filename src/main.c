#include "stm32f767xx.h"

#include "usart.h"
#include "timers.h"
#include "buttons.h"
#include "gpio.h"
#include "leds.h"

void __libc_init_array(void) {

}

int main() {
    USART3_GPIO_Init();
    USART3_Init();

    Button_Init();
    Leds_Init();

    while(1) {

    }
}

void ButtonClicked(void) {
    USART3_SendString("Single click\n\r");
}

void ButtonDoubleClicked(void) {
    USART3_SendString("Double click\n\r");
}

void ButtonLongPressed(void) {
    USART3_SendString("Long press\n\r");
}
