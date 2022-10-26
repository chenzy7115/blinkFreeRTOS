/* Blink 
    使用FreeRTOS实现BLink
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#define BLINK_GPIO 2 //定义GPIO

static uint8_t s_led_state = 0; //高低电平控制变量

void taskLedBlink(void *Param)
{
    while(1)
    {
        s_led_state = !s_led_state;
        if(s_led_state)
        {
            printf("LED ON\n");
        }
        else
        {
            printf("LED OFF\n");
        }
        gpio_set_level(BLINK_GPIO, s_led_state);//设置指定GPIO的状态
        vTaskDelay(pdMS_TO_TICKS(500));//控制闪烁频率，500MS转换一次
    }
}

static void configure_led(void)//初始化GPIO
{
    gpio_reset_pin(BLINK_GPIO);//重置GPIO状态，上拉
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);//设置GPIO为OUTPUT模式
}

void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();
    xTaskCreate(taskLedBlink,"taskLedBlink",1024*2,NULL,1,NULL);

}
