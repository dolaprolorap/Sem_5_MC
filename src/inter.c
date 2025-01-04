#include "inter.h"

struct DelayFunction {
    void(*func)(void);
    int cycles;
    uint8_t enable;
};

static struct DelayFunction delay_function[MAX_DELAY_FUNCTIONS];
static int next_function = 0;

int Delay_AddFunction(void(*func)(void), int cycles) {
    if (next_function >= MAX_DELAY_FUNCTIONS) {
        return -1;
    }

    delay_function[next_function].func = func;
    delay_function[next_function].cycles = cycles;
    delay_function[next_function].enable = TRUE;

    return next_function++;
}

void Delay_ChangeFunction(void(*func)(void), int cycles, int index) {
    delay_function[index].func = func;
    delay_function[index].cycles = cycles;
}

void Delay_ToggleFunction(int index, int8_t enable) {
    if (enable == NULL) {
        delay_function[index].enable = (delay_function[index].enable == TRUE) ? FALSE : TRUE;
        return;
    }

    delay_function[index].enable = enable;
}

void TIM2_IRQHandler(void) {
    static int counter = 0;

    for (int i = 0; i < next_function; i++) {
        if ((counter % delay_function[i].cycles == 0) && (delay_function[i].enable == TRUE)) {
            (delay_function[i].func)();
        }
    }

    counter = (counter + 1) % 100;
}
