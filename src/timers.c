#include "timers.h"

// static inline void TIM3_Init(void) {
//     RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
//     TIM3->ARR = PWM_TIMER_ARR;
//     TIM3->PSC = 0;

//     //Generate an update event to reload the Prescaler
//     //and the repetition counter value (if applicable) immediately
//     TIM3->EGR |= TIM_EGR_UG;
//     //Select the Output Compare Mode
//     TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
//     TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
//     //CH1 Enable Preload
//     TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
//     //Set the Output Compare Polarity (active - is high level)
//     TIM3->CCER &= ~TIM_CCER_CC1P;
//     //Set the Output State
//     TIM3->CCER |= TIM_CCER_CC1E;
//     //Set the Capture Compare Registers value
//     TIM3->CCR1 = 30000;
// }

static int tim_info_index = 0;

static int dir_pwm1 = PWM_DIR_FORWARD;
static int dir_pwm2 = PWM_DIR_FORWARD;

struct TIMInfo tims[] = {
    { 
        TIM5, 
        TIM_CCMR1_OC1M_Msk | TIM_CCMR1_OC1PE_Msk,
        TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE, 
        0,
        0,
        TIM_CCER_CC1E_Msk,
        TIM_CCER_CC1E,
        &TIM5->CCR1
    },
    { 
        TIM1, 
        TIM_CCMR1_OC1M_Msk | TIM_CCMR1_OC1PE_Msk,
        TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE, 
        0,
        0, 
        TIM_CCER_CC1E_Msk,
        TIM_CCER_CC1E,
        &TIM1->CCR1 
    },
    { 
        TIM5, 
        0,
        0,
        TIM_CCMR2_OC4M_Msk | TIM_CCMR2_OC4PE_Msk,
        TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE,
        TIM_CCER_CC4E_Msk,
        TIM_CCER_CC4E,
        &TIM5->CCR4
    },
    { 
        TIM1, 
        TIM_CCMR1_OC2M_Msk | TIM_CCMR1_OC2PE_Msk,
        TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE, 
        0,
        0, 
        TIM_CCER_CC2E_Msk,
        TIM_CCER_CC2E,
        &TIM1->CCR2 
    },
};

// 10 milliseconds
static inline void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->PSC = 15;
    TIM2->ARR = 10000;
}

static inline void TIM_PWM_Enable(struct TIMInfo* tim_info) {
    tim_info->tim->CCER &= ~tim_info->ccer_msk;
    tim_info->tim->CCER |= tim_info->ccer;
}

static inline void TIM_PWM_Disable(struct TIMInfo* tim_info) {
    tim_info->tim->CCER &= ~tim_info->ccer_msk;
}

static inline void TIM_PWM_ChangeDutyCicle(int* dir, int duty_per_cicle, struct TIMInfo* tim_info) {
    switch(*dir) {
        case PWM_DIR_FORWARD:
            if ((int32_t)(*tim_info->ccr + duty_per_cicle) >= PWM_TIMER_ARR) {
                *tim_info->ccr = PWM_TIMER_ARR - 1;
                *dir = PWM_DIR_BACKWARD;
            }
            else {
                *tim_info->ccr += duty_per_cicle;
            }
            break;
        case PWM_DIR_BACKWARD:
            if ((int32_t)(*tim_info->ccr - duty_per_cicle) < 0) {
                *tim_info->ccr = 0;
                *dir = PWM_DIR_FORWARD;
            }
            else {
                *tim_info->ccr -= duty_per_cicle;
            }
            break;
    }
}

void TIMs_PWM_ChangeDutyCicle(void) {
    TIM_PWM_ChangeDutyCicle(&dir_pwm1, PWM1_DUTY_PER_CICLE, &tims[tim_info_index % TIMERS_COUNT]);
    TIM_PWM_ChangeDutyCicle(&dir_pwm2, PWM2_DUTY_PER_CICLE, &tims[(tim_info_index + 1) % TIMERS_COUNT]);
}

void Change_PWM_TIMs(void) {
    TIM_PWM_Disable(&tims[tim_info_index % TIMERS_COUNT]);
    TIM_PWM_Disable(&tims[(tim_info_index + 1) % TIMERS_COUNT]);

    tim_info_index = (tim_info_index + 1) % TIMERS_COUNT;

    TIM_PWM_Enable(&tims[tim_info_index % TIMERS_COUNT]);
    TIM_PWM_Enable(&tims[(tim_info_index + 1) % TIMERS_COUNT]);
}

void TIMs_Init(void) {
    TIM2_Init();

    TIM_EnableCounter(TIM2);
    TIM_EnableIT_UPDATE(TIM2);

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

    for (int i = 0; i < TIMERS_COUNT; i++) {
        tims[i].tim->ARR = PWM_TIMER_ARR;
        tims[i].tim->PSC = 0;
        tims[i].tim->EGR |= TIM_EGR_UG;

        tims[i].tim->CCMR1 &= ~tims[i].ccmr1_msk;
        tims[i].tim->CCMR1 |= tims[i].ccmr1;

        tims[i].tim->CCMR2 &= ~tims[i].ccmr2_msk;
        tims[i].tim->CCMR2 |= tims[i].ccmr2;
    }

    TIM_EnableCounter(TIM1);
    TIM_EnableCounter(TIM5);

    TIM1->BDTR |= TIM_BDTR_MOE;

    Change_PWM_TIMs();
}
