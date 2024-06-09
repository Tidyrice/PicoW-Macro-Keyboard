#include "../inc/button_callback.h"
#include "tusb.h"
#include "bsp/board.h"
#include "config.h"
#include "../inc/usb_descriptors.h"

void button_callback(uint gpio, uint32_t events) {
    static bool pressed = false;

    if (!pressed) { //button down
        uint8_t modifier = KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTGUI;
        uint8_t keycode[6] = {0};

        if (gpio == BUTTON_INPUT_PIN1) { //LEFTCTRL + LEFTGUI (windows key) + ARROW_LEFT (prev desktop)
            keycode[0] = HID_KEY_ARROW_LEFT;
            printf("LEFT\n");
        }
        else if (gpio == BUTTON_INPUT_PIN2) { //LEFTCTRL + LEFTGUI (windows key) + ARROW_RIGHT (next desktop)
            keycode[0] = HID_KEY_ARROW_RIGHT;
            printf("RIGHT\n");
        }

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);
        pressed = true;
    }
    else {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        pressed = false;
    }
}