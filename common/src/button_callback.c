#include "../inc/button_callback.h"
#include "tusb.h"
#include "bsp/board.h"
#include "config.h"
#include "../inc/usb_descriptors.h"

volatile button_state_t button1_state = BUTTON_STATE_IDLE;
volatile button_state_t button2_state = BUTTON_STATE_IDLE;
volatile uint32_t last_interrupt_time = 0;

void button_callback(uint gpio, uint32_t events) {
    if (events == GPIO_IRQ_EDGE_RISE) { //button down
        //software button debounce
        uint32_t current_time = to_ms_since_boot(get_absolute_time());
        if (current_time - last_interrupt_time < BUTTON_DEBOUNCE_TIME_MS) {
            return;
        }
        last_interrupt_time = current_time;

        //construct and send keyboard event
        uint8_t modifier = KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTGUI;
        uint8_t keycode[6] = {0};

        if (gpio == BUTTON_INPUT_PIN1 && button1_state == BUTTON_STATE_IDLE) {
            keycode[0] = HID_KEY_ARROW_LEFT; //LEFTCTRL + LEFTGUI (windows key) + ARROW_LEFT (prev desktop)
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);
            button1_state = BUTTON_STATE_PRESSED;
        }
        else if (gpio == BUTTON_INPUT_PIN2 && button2_state == BUTTON_STATE_IDLE) {
            keycode[0] = HID_KEY_ARROW_RIGHT; //LEFTCTRL + LEFTGUI (windows key) + ARROW_RIGHT (next desktop)
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);
            button2_state = BUTTON_STATE_PRESSED;
        }

    }
    else { //button up
        if (gpio == BUTTON_INPUT_PIN1 && button1_state == BUTTON_STATE_PRESSED) {
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); //release event
            button1_state = BUTTON_STATE_IDLE;
        }
        else if (gpio == BUTTON_INPUT_PIN2 && button2_state == BUTTON_STATE_PRESSED) {
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); //release event
            button2_state = BUTTON_STATE_IDLE;
        }
    }
}