#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"

#include "config.h"
#include "common/inc/button_callback.h"

int main() {
    //INITIALIZATION
    board_init();
    stdio_init_all(); //initialize serial port (default 115200 bits/s)
    tud_init(BOARD_DEVICE_RHPORT_NUM);

    //GPIO init
    uint GPIO_BITMASK = (1 << BUTTON_INPUT_PIN1) | (1 << BUTTON_INPUT_PIN2);
    gpio_init_mask(GPIO_BITMASK);
    gpio_set_dir_in_masked(GPIO_BITMASK);

    //IRQ init
    gpio_set_irq_enabled_with_callback(BUTTON_INPUT_PIN1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_INPUT_PIN2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_callback);

    //WIFI init
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    //wait forever
    while (1) {
        tud_task();
    }
}