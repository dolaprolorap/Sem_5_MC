#ifndef LEDS_H
#define LEDS_H

#include "stm32f767xx.h"
#include "timers.h"
#include "gpio.h"

#define FIRST_STATUS 0
#define SECOND_STATUS 1

struct LedInfo {
    GPIO_TypeDef* PORT;
    int PIN;
};

void Leds_Init(void);
void Leds_SetStatus(int);
void Leds_Shift(void);

#endif
