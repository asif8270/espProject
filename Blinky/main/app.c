#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "driver/gpio.h"

#define LED_GPIO GPIO_NUM_2

void blinkLED(void);

void app_main(void)
{
    xTaskCreate((void *)blinkLED, "Blinky", 1024, NULL, 5, NULL);
}

void blinkLED(void)
{
    gpio_config_t ledGPIO;
    ledGPIO.intr_type = GPIO_INTR_DISABLE;
    ledGPIO.mode = GPIO_MODE_OUTPUT;
    ledGPIO.pin_bit_mask = (1ULL << LED_GPIO);
    ledGPIO.pull_down_en = 0;
    ledGPIO.pull_up_en = 0;

    esp_err_t err = gpio_config(&ledGPIO);
    if (err != ESP_OK)
    {
        printf("\rError occured in GPIO configuration: %c\n", err);
    }
    else
    {
        printf("\rGPIO configured successfully\n");
    }

    while (1)
    {
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(100);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(100);
    }
}