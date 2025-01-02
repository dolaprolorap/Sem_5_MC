#include "inter.h"

void TIM2_IRQHandler(void) {
    Button_ClickManagerHandler();
}
