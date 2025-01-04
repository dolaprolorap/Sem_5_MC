#ifndef INTER_H
#define INTER_H

#include "stm32f767xx.h"
#include "general.h"

#define MAX_DELAY_FUNCTIONS 10

int Delay_AddFunction(void(*)(void), int);
void Delay_ChangeFunction(void(*)(void), int, int);
void Delay_ToggleFunction(int, int8_t);

#endif // INTER_H
