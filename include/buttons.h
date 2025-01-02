#ifndef BUTTONS_H
#define BUTTONS_H

#include "stm32f767xx.h"
#include "timers.h"

void Button_Init(void);
int Button_IsPressed(void);

extern void ButtonClicked(void);
extern void ButtonDoubleClicked(void);
extern void ButtonLongPressed(void);

#endif
