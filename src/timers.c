#include "timers.h"

static inline void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->PSC = 15;
    TIM2->ARR = 10000;
}

static inline void TIM3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->ARR = 65535;
    TIM3->PSC = 0;

    //Generate an update event to reload the Prescaler
    //and the repetition counter value (if applicable) immediately
    TIM3->EGR |= TIM_EGR_UG;
    //Select the Output Compare Mode
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    //CH1 Enable Preload
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    //Set the Output Compare Polarity (active - is high level)
    TIM3->CCER &= ~TIM_CCER_CC1P;
    //Set the Output State
    TIM3->CCER |= TIM_CCER_CC1E;
    //Set the Capture Compare Registers value
    TIM3->CCR1 = 30000;
}

void TIM_PWM1_Init(void) {
    TIM3_Init();

    TIM_EnableCounter(TIM3);
}

void TIM_PWM2_Init(void) {

}

void TIM_ClickManager_Init(void) {
    TIM2_Init();

    TIM_EnableIT_UPDATE(TIM2);
    TIM_EnableCounter(TIM2);
}
