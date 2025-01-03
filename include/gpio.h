#ifndef GPIO_H
#define GPIO_H

#include "stm32f767xx.h"

#define GPIO_COUNT 4

void Change_GPIOs(void);
void GPIO_Init(void);
void Toggle_FirstBlinkingLED(void);
void Toggle_SecondBlinkingLED(void);

#endif
