#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "config.h"
#include "common/inc/usb_descriptors.h"

void buttonInterruptHandler (uint gpio, uint32_t events) {
    //RISING EDGE: bit 3 == 1 (8u)
    //FALLING EDGE: bit 2 == 1 (4u)

    (events & (1 << 3)) ? printf("%d RISING EDGE\n", gpio) : printf("%d FALLING EDGE\n", gpio);
}

void hid_task(void);

int main() {
    //INITIALIZATION
    stdio_init_all(); //initialize serial port (default 115200 bits/s)
    tusb_init(); //initialize TinyUSB

    //GPIO init
    const uint leftButtonPin = BUTTON_INPUT_PIN1;
    const uint rightButtonPin = BUTTON_INPUT_PIN2;
    gpio_init(leftButtonPin);
    gpio_init(rightButtonPin);
    gpio_set_dir(leftButtonPin, GPIO_IN);
    gpio_set_dir(rightButtonPin, GPIO_IN);

    //IRQ init
    gpio_set_irq_enabled_with_callback(leftButtonPin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &buttonInterruptHandler);
    gpio_set_irq_enabled_with_callback(rightButtonPin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &buttonInterruptHandler);

    //WIFI init
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    //wait forever
    while (1) {
        tud_task(); // tinyusb device task
        
        //other tasks

        hid_task();
    }
}