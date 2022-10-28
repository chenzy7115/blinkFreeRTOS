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

#define GREEN_GPIO 2 //定义GPIO
#define BLUE_GPIO 4 //定义GPIO
#define RED_GPIO 0 //定义GPIO

void taskLedBlink1(void *Param)
{
    static uint8_t s_led_state1 = 0; //高低电平控制变量
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));//控制闪烁频率，500MS转换一次
        s_led_state1 = !s_led_state1;
        if(s_led_state1)
        {
            printf("GREEN_GPIO ON\n");
        }
        else
        {
            printf("GREEN_GPIO OFF\n");
        }
        gpio_set_level(GREEN_GPIO, s_led_state1);//设置指定GPIO的状态
        
    }
}
void taskLedBlink2(void *Param)
{
    static uint8_t s_led_state2 = 0; //高低电平控制变量
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));//控制闪烁频率，500MS转换一次
        s_led_state2 = !s_led_state2;
        if(s_led_state2)
        {
            printf("BLUE_GPIO ON\n");
        }
        else
        {
            printf("BLUE_GPIO OFF\n");
        }
        gpio_set_level(BLUE_GPIO, s_led_state2);//设置指定GPIO的状态
        
    }
}

void taskLedBlink3(void *Param)
{
    static uint8_t s_led_state3 = 0; //高低电平控制变量
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));//控制闪烁频率，500MS转换一次
        s_led_state3 = !s_led_state3;
        if(s_led_state3)
        {
            printf("RED_GPIO ON\n");
        }
        else
        {
            printf("RED_GPIO OFF\n");
        }
        gpio_set_level(RED_GPIO, s_led_state3);//设置指定GPIO的状态
        
    }
}

static void configure_led(void)//初始化GPIO
{
    gpio_reset_pin(GREEN_GPIO);//重置GPIO状态，上拉
    gpio_reset_pin(BLUE_GPIO);
    gpio_reset_pin(RED_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GREEN_GPIO, GPIO_MODE_OUTPUT);//设置GPIO为OUTPUT模式
    gpio_set_direction(BLUE_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(RED_GPIO, GPIO_MODE_OUTPUT);
}

void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();
    xTaskCreate(taskLedBlink1,"taskLedBlink1",1024*2,NULL,1,NULL);
    xTaskCreate(taskLedBlink2,"taskLedBlink2",1024*2,NULL,1,NULL);
    xTaskCreate(taskLedBlink3,"taskLedBlink3",1024*2,NULL,1,NULL);

}
