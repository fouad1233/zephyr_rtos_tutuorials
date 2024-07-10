#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#define LED0_NODE DT_NODELABEL(green_led)


int counter = 30;
void increment_counter(void);

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void){
    
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    //Configure button as input
    
    
    while(true){
        increment_counter();
        gpio_pin_toggle_dt(&led);
        k_msleep(100); // Sleep for 1 second
        
    }
    return 0;
}
void increment_counter(){
    counter = counter + 1;
}
    




