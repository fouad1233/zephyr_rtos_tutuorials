#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define GPIO_PIN 13
int counter = 30;
static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpiod));
void increment_counter(void);
int main(void){
    if (!device_is_ready(gpio_ct_dev)) {
        //printk("GPIO device %s is not ready\n", gpio_ct_dev->name);
        return 1;
    }
    int gpio_conf;
    gpio_conf = gpio_pin_configure(gpio_ct_dev,GPIO_PIN, GPIO_OUTPUT_ACTIVE);

    counter = counter + 1;

    int pin_set = 0;
    while(true){
        increment_counter();
        pin_set = gpio_pin_set_raw(gpio_ct_dev, GPIO_PIN, 1);
        //printk("Hello World\n");
        k_msleep(1000); // Sleep for 1 second
        pin_set = gpio_pin_set_raw(gpio_ct_dev, GPIO_PIN, 0);
        
        k_msleep(1000); // Sleep for 1 second
    }
    return 0;
}
void increment_counter(){
    counter = counter + 1;
}
    




