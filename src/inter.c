#include "inter.h"

void TIM2_IRQHandler(void) {
    static int blink_counter = 0;

    if (blink_counter % 50 == 0) {
        Toggle_SecondBlinkingLED();
    }

    if (blink_counter % 100 == 0) {
        Toggle_FirstBlinkingLED();
    }

    blink_counter = (blink_counter + 1) % 100;

    Button_ClickManagerHandler();
    TIMs_PWM_ChangeDutyCicle();
}
