#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "config.h"
#include "common/inc/usb_descriptors.h"

void button_callback(uint gpio, uint32_t events) {
    static bool pressed = false;

    if (!pressed) { //button down
        uint8_t modifier = KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTGUI;
        uint8_t keycode[6] = {0};

        if (gpio == BUTTON_INPUT_PIN1) { //LEFTCTRL + LEFTGUI (windows key) + ARROW_LEFT (prev desktop)
            keycode[0] = HID_KEY_ARROW_LEFT;
        }
        else if (gpio == BUTTON_INPUT_PIN2) { //LEFTCTRL + LEFTGUI (windows key) + ARROW_RIGHT (next desktop)
            keycode[0] = HID_KEY_ARROW_RIGHT;
        }

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);
        pressed = true;
    }
    else {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        pressed = false;
    }
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
    gpio_set_irq_enabled_with_callback(leftButtonPin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(rightButtonPin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_callback);

    //WIFI init
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    //wait forever
    while (1) {
        tud_task(); // tinyusb device task
    }
}