#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

#define GPIO_PIN 13
#define LED0_NODE DT_NODELABEL(blinking_led)


/*Function prototypes*/
void increment_counter(void);
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

/*Variables*/
int counter = 0;
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_NODELABEL(my_button), gpios);
static struct gpio_callback button_cb_data;


int main(void){
    if (!device_is_ready(led.port)) {
        return 1;
    }
    if (!device_is_ready(button.port)) {
        return 1;
    }
    
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    
    gpio_pin_configure_dt(&button, GPIO_INPUT);

    //set the interrupts 
    // Configure the button pin to trigger an interrupt on the rising edge
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE); 
    // Set up the callback function to be called when the button is pressed
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    // Enable the interrupt for the button pin
    gpio_add_callback(button.port, &button_cb_data);

    


    while(true){
        
    }
    return 0;
}


void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins){
    /* The arguments are 
    * dev: The device that triggered the interrupt
    * cb: The callback structure that was triggered
    * pins: The pin that triggered the interrupt
    */
    increment_counter();
    gpio_pin_toggle_dt(&led);
}

void increment_counter(void){
    counter = counter + 1;
}
    




