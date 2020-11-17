//
// Created by 10612 on 2020/11/17.
//

#include "main.h"
#include "bsp_led.h"
#include "bsp_key.h"

bool_t exit_flag = 0;
bool_t rising_falling_flag = 0;
void key_led_loop(void) {
    if (exit_flag == 1) {
        exit_flag = 0;
        if (rising_falling_flag == GPIO_PIN_RESET) {
            HAL_Delay(20);
            if (HAL_GPIO_ReadPin(USER_KEY_GPIO_Port, USER_KEY_Pin) == GPIO_PIN_RESET) {
                led_on();
                exit_flag = 0;
            } else {
                exit_flag = 0;
            }

        } else if (rising_falling_flag == GPIO_PIN_SET) {
            HAL_Delay(20);
            if (HAL_GPIO_ReadPin(USER_KEY_GPIO_Port, USER_KEY_Pin) == GPIO_PIN_SET) {
                led_off();
                exit_flag = 0;
            } else {
                exit_flag = 0;
            }

        }

    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == USER_KEY_Pin) {
        if (exit_flag == 0) {
            exit_flag = 1;
            rising_falling_flag = HAL_GPIO_ReadPin(USER_KEY_GPIO_Port, USER_KEY_Pin);
        }
    }
}
