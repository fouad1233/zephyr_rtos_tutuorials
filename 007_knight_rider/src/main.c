#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

#define LED0_NODE DT_NODELABEL(green_led)
#define OUT1_NODE DT_NODELABEL(out1)
#define OUT2_NODE DT_NODELABEL(out2)
#define OUT3_NODE DT_NODELABEL(out3)
#define OUT4_NODE DT_NODELABEL(out4)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec out1 = GPIO_DT_SPEC_GET(OUT1_NODE, gpios);
static const struct gpio_dt_spec out2 = GPIO_DT_SPEC_GET(OUT2_NODE, gpios);
static const struct gpio_dt_spec out3 = GPIO_DT_SPEC_GET(OUT3_NODE, gpios);
static const struct gpio_dt_spec out4 = GPIO_DT_SPEC_GET(OUT4_NODE, gpios);

static const struct gpio_dt_spec *leds[] = { &out1, &out2, &out3, &out4};

void configure_leds(void) {
    for (int i = 0; i < ARRAY_SIZE(leds); i++) {
        if (!device_is_ready(leds[i]->port)) {
            printk("Error: LED device %s is not ready\n", leds[i]->port->name);
            return;
        }
        gpio_pin_configure_dt(leds[i], GPIO_OUTPUT_INACTIVE);
    }
}

void knight_rider_effect(void) {
    int i;
    int direction = 1;

    while (1) {
        for (i = 0; i < ARRAY_SIZE(leds);i += direction) {
            gpio_pin_set(leds[i]->port, leds[i]->pin, 1);
            k_msleep(100);
            gpio_pin_set(leds[i]->port, leds[i]->pin, 0);

            if (i == ARRAY_SIZE(leds) - 1 || i == 0) {
                direction = -direction;
            }
            
        }
    }
}

int main(void) {
    configure_leds();
    knight_rider_effect();
    return 0;
}
