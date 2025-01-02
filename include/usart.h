#ifndef USART_H
#define USART_H

#include "stm32f767xx.h"

#define BAUD_RATE 115200

void USART3_GPIO_Init(void);
void USART3_Init(void);
void USART3_SendString(const char *str);

#endif
