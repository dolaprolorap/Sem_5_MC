#ifndef LED_H
#define LED_H

#include "stm32f767xx.h"
#include "gpio.h"
#include "inter.h"
#include "timers.h"

#define FIRST_MODE 0
#define SECOND_MODE 1

#define SPEEDS_COUNT 3

extern int mode;

void LEDs_Init(void);
void LEDs_ToggleMode(void);
void LEDs_Switch(void);

#endif // LED_H
