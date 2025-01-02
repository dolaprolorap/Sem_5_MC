#include "usart.h"

// PD8, PD9
void USART3_GPIO_Init(void) {
    // Включаем тактирование GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // Устанавливаем PD8, PD9 в режим альтернативной функции
    GPIOD->MODER &= ~(GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
    GPIOD->MODER |= (GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1);

    // Выбираем альтернативную функцию AF7 для USART3 (AF7 = 0x7)
    GPIOD->AFR[1] |= (7 << GPIO_AFRH_AFRH0_Pos) | (7 << GPIO_AFRH_AFRH1_Pos);

    // Устанавливаем скорость вывода
    GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9;
}

void USART3_Init(void) {
    // Включаем тактирование USART3
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    // Устанавливаем скорость передачи данных (пример для 115200 бод)
    USART3->BRR = SystemCoreClock / BAUD_RATE;

    // Включаем USART2, передатчик и приёмник
    USART3->CR1 = USART_CR1_TE | USART_CR1_UE;
}

void USART3_SendString(const char *str) {
    while (*str) {
        // Ждем, пока буфер передатчика освободится
        while (!(USART3->ISR & USART_ISR_TXE));
        
        // Отправляем байт
        USART3->TDR = *str++;
    }
}

