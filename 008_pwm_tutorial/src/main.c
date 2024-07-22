#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/pwm.h>
//#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

//LOG_MODULE_REGISTER(pwm_sample, LOG_LEVEL_INF);

#define PWM_CHANNEL 1
#define LED0_NODE DT_NODELABEL(green_led)


static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct pwm_dt_spec green_pwm_led = PWM_DT_SPEC_GET(DT_NODELABEL(green_pwm_led));
int ret;
int main(void)
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (!device_is_ready(green_pwm_led.dev)) {
        printk("PWM device  is not ready\n");
        return -ENODEV;
    }

    
    while (true)
    {
        ret = pwm_set_pulse_dt(&green_pwm_led,0);
        gpio_pin_toggle_dt(&led);
        k_sleep(K_MSEC(1000));
        ret = pwm_set_pulse_dt(&green_pwm_led,10000);
        gpio_pin_toggle_dt(&led);
        k_sleep(K_MSEC(1000));
    }
    
    return 0;
}
