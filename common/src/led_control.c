#include "../inc/led_control.h"
#include "pico/cyw43_arch.h"

volatile bool led_blink_flag = false;
uint32_t led_blink_end_time = 0;

void check_handle_led_blink() {
    if (led_blink_flag) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        led_blink_end_time = to_ms_since_boot(get_absolute_time()) + 100; //stay on for 100ms
        led_blink_flag = false;
    }

    if (led_blink_end_time && to_ms_since_boot(get_absolute_time()) >= led_blink_end_time) { //time to turn LED off
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        led_blink_end_time = 0;
    }
}