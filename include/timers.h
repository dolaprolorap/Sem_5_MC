#ifndef TIMERS_H
#define TIMERS_H

#include "stm32f767xx.h"

#define CLOCK_FREQ 16000000u

#define TIM_EnableIT_UPDATE(TIMx) TIMx->DIER |= TIM_DIER_UIE
#define TIM_EnableCounter(TIMx) TIMx->CR1 |= TIM_CR1_CEN
#define TIM_DisableCounter(TIMx) TIMx->CR1 &= ~TIM_CR1_CEN

void TIM_PWM1_Init(void);
void TIM_PWM2_Init(void);
void TIM_ClickManager_Init(void);

#endif
