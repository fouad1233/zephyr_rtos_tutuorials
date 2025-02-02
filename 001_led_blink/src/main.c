#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>


#define GPIO_PIN 13
#define LED0_NODE DT_NODELABEL(blinking_led)
#define LED1_NODE DT_ALIAS(led2)

LOG_MODULE_REGISTER(main, CONFIG_MAIN_LOG_LEVEL);

int counter = 30;
//#if DT_NODE_HAS_STATUS(MY_SERIAL, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
//#else
//#error "Node is disabled"
//#endif

void increment_counter(void);
int main(void){
    if (!device_is_ready(led0.port)) {
        //printk("GPIO device %s is not ready\n", gpio_ct_dev->name);
        return 1;
    }
    int gpio_conf;
    //gpio_conf = gpio_pin_configure(led.port,led.pin, led.dt_flags);
    gpio_conf = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	gpio_conf = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    //GPIO_OUTPUT_ACTIVE (or GPIO_OUTPUT_INACTIVE): Configures a GPIO pin
    // as an output and sets its initial state to the active (or inactive) state.
    counter = counter + 1;

    int pin_set = 0;
    while(true){
        increment_counter();
		// log the counter value with LOG_DBG
		LOG_INF("Counter value: %d", counter);
        //pin_set = gpio_pin_set_raw(led.port, led.pin, 1);
        //pin_set = gpio_pin_set_dt(&led, 1);
        pin_set = gpio_pin_toggle_dt(&led0);
        k_msleep(100); // Sleep for 1 second
		pin_set = gpio_pin_toggle_dt(&led1);
        k_msleep(100); // Sleep for 1 second
        //pin_set = gpio_pin_set_dt(&led, 0);
        //k_msleep(1000); // Sleep for 1 second
    }
    return 0;
}
void increment_counter(){
    counter = counter + 1;
}
    
