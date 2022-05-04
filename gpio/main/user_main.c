/* gpio example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"

#ifndef HIGH_ON
#define HIGH_ON 1
#endif

#ifndef LOW_OFF
#define LOW_OFF 0
#endif

/**
 * Brief:
 * This test code shows how to configure gpio and how to blink inbuild led at GPIO 16
 *
 * GPIO status:
 * GPIO16: output
 *
 * Test:
 * Inbuilt LED should be blinking every half a second
 *
 */

#define BUILTIN_LED 16
#define GPIO_OUTPUT_PIN_SEL (1<<BUILTIN_LED)

static void gpio_blink_led(void *arg)
{
	gpio_set_level(BUILTIN_LED, HIGH_ON);
	vTaskDelay(500 / portTICK_RATE_MS);
	gpio_set_level(BUILTIN_LED, LOW_OFF);
	vTaskDelay(500 / portTICK_RATE_MS);
}

void app_main(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
	
	// Creating and starting task
	xTaskCreate(gpio_blink_led,
		"gpio_blink_led",
		1024,
		NULL,
		1,
		NULL);
}


