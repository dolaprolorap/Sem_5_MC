#ifndef GPIO_H
#define GPIO_H

#include "stm32f767xx.h"
#include "general.h"

#define GPIO_COUNT 4

void GPIO_InitLEDs(void);

void GPIO_ToggleFirstBlinkingLED(void);
void GPIO_ToggleSecondBlinkingLED(void);

void GPIO_LightNextLEDInChain(void);
void GPIO_SwitchLEDsSecondMode(void);
void GPIO_SwitchLEDsFirstMode(void);

void GPIO_SetFirstMode(void);
void GPIO_SetSecondMode(void);

#endif
