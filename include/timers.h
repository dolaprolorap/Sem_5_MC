#ifndef TIMERS_H
#define TIMERS_H

#include "stm32f767xx.h"
#include "usart.h"

#define PWM_DIR_FORWARD 0
#define PWM_DIR_BACKWARD 1

#define PWM1_DUTY_PER_CICLE 1000
#define PWM2_DUTY_PER_CICLE 2000

#define PWM_TIMER_ARR 50000

#define TIM_EnableIT_UPDATE(TIMx) TIMx->DIER |= TIM_DIER_UIE
#define TIM_EnableCounter(TIMx) TIMx->CR1 |= TIM_CR1_CEN
#define TIM_DisableCounter(TIMx) TIMx->CR1 &= ~TIM_CR1_CEN

#define TIMERS_COUNT 4

struct TIMInfo {
    TIM_TypeDef* tim;
    uint32_t ccmr1_msk;
    uint32_t ccmr1;
    uint32_t ccmr2_msk;
    uint32_t ccmr2;
    uint32_t ccer_msk;
    uint32_t ccer;
    volatile uint32_t* ccr;
};

extern struct TIMInfo tims[];

void TIMs_PWM_ChangeDutyCicle(void);
void Change_PWM_TIMs(void);
void TIMs_Init(void);

void TIM_PWMTIMsInit(void);
void TIM_DelayTIMInit(void);

#endif
