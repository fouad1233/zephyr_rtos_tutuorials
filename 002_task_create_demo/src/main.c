#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>

//LOG_MODULE_REGISTER(main);

/* Constants */
#define STACKSIZE 1024
#define TOGGLE_LED_PRIORITY 1
#define INCREMENT_COUNTER_PRIORITY 2

#define LED0_NODE DT_NODELABEL(blinking_led)

/* Function Prototypes */
void increment_counter(void *a, void *b, void *c);
void blink_led(void *a, void *b, void *c);

/* Global Variables */
int counter = 30;
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

K_THREAD_DEFINE(toggle_led_tid, STACKSIZE, blink_led,
                 NULL, NULL, NULL, TOGGLE_LED_PRIORITY, 0, 0);
K_THREAD_DEFINE(increment_counter_tid, STACKSIZE, increment_counter,
                 NULL, NULL, NULL, INCREMENT_COUNTER_PRIORITY, 0, 0);

int main(void) {
    if (!device_is_ready(led.port)) {
        //LOG_ERR("GPIO device %s is not ready", led.port->name);
        return 1;
    }

    int gpio_conf = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (gpio_conf < 0) {
        //LOG_ERR("Failed to configure GPIO pin: %d", gpio_conf);
        return 1;
    }

    while (1) {
        k_sleep(K_MSEC(1000)); // Sleep to prevent main from exiting
    }

    return 0;
}

void blink_led(void *a, void *b, void *c) {
    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(1000); // Sleep for 1 second
    }
}

void increment_counter(void *a, void *b, void *c) {
    while (1) {
        counter++;
        //k_msleep(1); // Sleep to prevent busy-waiting
    }
}
