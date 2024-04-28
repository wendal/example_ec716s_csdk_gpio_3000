#include "common_api.h"
#include "luat_rtos.h" //luat 头文件 封装FreeRTOS
#include "luat_debug.h"//luat DBUG 库
#include "luat_gpio.h"//luat GPIO 库
#include "platform_define.h"
#include "pad.h"
#include "luat_pm.h"
#ifndef CHIP_EC716
#define GPIO_LED_PIN HAL_GPIO_27
#else
#define GPIO_LED_PIN HAL_GPIO_14
#endif
luat_rtos_timer_t pwrkey_timerHand;
/********************************************GPIO 点亮led GPIO27 start*******************************************/
void net_led_init(void)
{
    luat_gpio_cfg_t Net_led_struct;

    luat_pm_iovolt_ctrl(LUAT_PM_ALL_GPIO, 3000);

    luat_gpio_set_default_cfg(&Net_led_struct);
    Net_led_struct.pin=8;
    Net_led_struct.pull=Luat_GPIO_PULLUP;
    Net_led_struct.mode=Luat_GPIO_OUTPUT;
    Net_led_struct.output_level=Luat_GPIO_HIGH;
    luat_gpio_open(&Net_led_struct);

    
    luat_gpio_set_default_cfg(&Net_led_struct);
    Net_led_struct.pin=9;
    Net_led_struct.pull=Luat_GPIO_PULLUP;
    Net_led_struct.mode=Luat_GPIO_OUTPUT;
    Net_led_struct.output_level=Luat_GPIO_HIGH;
    luat_gpio_open(&Net_led_struct);

    
    LUAT_DEBUG_PRINT("GPIO8/9设置输出电平为3.0v, 内部拉高");
}

static void net_led_task(void *param)
{
    net_led_init();
    while (1)
    {
        luat_rtos_task_sleep(5000);
        LUAT_DEBUG_PRINT("设置成低电平");
        luat_gpio_set(8,0);
        luat_gpio_set(9,0);

        luat_rtos_task_sleep(5000);
        LUAT_DEBUG_PRINT("设置为高电平");
        luat_gpio_set(8,1);
        luat_gpio_set(9,1);
    }
    
}

void net_led_demo(void)
{
    luat_rtos_task_handle net_led_task_handler;
    luat_rtos_task_create(&net_led_task_handler,2*1024,50,"net_led_task",net_led_task,NULL,0);
}



/********************************************GPIO 中断功能     end *******************************************/

INIT_TASK_EXPORT(net_led_demo,"1");
// INIT_TASK_EXPORT(gpio_fun_demo,"2");
// INIT_TASK_EXPORT(gpio_interrupt_demo,"3");
