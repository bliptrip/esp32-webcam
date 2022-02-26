//Code to control an switching AC voltage dimmer using PWM.  In this case, 
//although the PWM signal is used to control high-intensity COB LEDs with 
//AC input voltages, I use the Motor Control Pulse Width Modulator
//(MCPWM) espressif driver module API (https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/mcpwm.html)
//because of its support to synchronize PWM timer modules through a GPIO signal.
//In this case, I use the zero-cross signal as synchronization input, and run the
//PWM at multiples of the input AC voltage frequency (60Hz United States, 50Hz most other countries).  The duty
//cycle is then set from 0 to 100% to set the output intensity.
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "esp_log.h"
#include "app_dimmer.h"

#ifdef CONFIG_DIMMER_ENABLED

#ifndef CONFIG_DIMMER_GPIO_0A
#define CONFIG_DIMMER_GPIO_0A 12
#endif
#ifndef CONFIG_DIMMER_GPIO_0B
#define CONFIG_DIMMER_GPIO_0B 13
#endif
#ifndef CONFIG_DIMMER_ZC_GPIO_0
#define CONFIG_DIMMER_ZC_GPIO_0 15
#endif

static const char *TAG = "DIMMER";

void app_dimmer_startup() {
	//1. mcpwm gpio initialization
    ESP_LOGI(TAG, "Initializing MCPWM gpio...\n");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, CONFIG_DIMMER_GPIO_0A);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, CONFIG_DIMMER_GPIO_0B);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_SYNC_0, CONFIG_DIMMER_ZC_GPIO_0);
	gpio_pulldown_en(CONFIG_DIMMER_ZC_GPIO_0);   //Enable pull down on Zero-Cross sync signal 

    //2. initialize mcpwm configuration
    ESP_LOGI(TAG, "Configuring Initial Parameters of mcpwm...\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 120;    //frequency = 120Hz 
    pwm_config.cmpr_a = 50.0;       //duty cycle of PWMxA = 50.0%
    pwm_config.cmpr_b = 50.0;       //duty cycle of PWMxb = 50.0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);   //Configure PWM0A & PWM0B with above settings

	//3. Enable synchronization
	mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_SELECT_SYNC0, 0);    //Load counter value with 0% of period counter of mcpwm timer 1 when sync 0 occurs

	//4. Start MCPWM unit.
    ESP_LOGI(TAG, "Starting mcpwm unit ...\n");
	mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_0);
}

void app_dimmer_shutdown() {
    ESP_LOGI(TAG, "Stopping mcpwm unit ...\n");
	mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
}

void app_dimmer_set_intensity(float duty) {      // Turn LED On or Off
    float _duty = duty;
    _duty = _duty > 100.0 ? 100.0 : _duty;
	_duty = _duty < 0.0 ? 0.0 : _duty;
    
	mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0A, _duty);
	mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0B, _duty);
    ESP_LOGI(TAG, "Set dimmer intensity to %f", _duty);
}


#endif
