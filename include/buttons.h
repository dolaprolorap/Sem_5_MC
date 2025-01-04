#ifndef BUTTONS_H
#define BUTTONS_H

#include "stm32f767xx.h"
#include "timers.h"
#include "inter.h"
#include "general.h"

void Button_Init(void);
int Button_IsPressed(void);

void Button_ClickManagerHandler(void);

extern void ButtonClicked(void);
extern void ButtonDoubleClicked(void);
extern void ButtonLongPressed(void);

#endif
