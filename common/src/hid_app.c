#include "../inc/hid_app.h"
#include "tusb.h"
#include <stdio.h>
#include "../inc/led_control.h"

#include "pico/cyw43_arch.h"

// HID Callbacks

uint16_t tud_hid_get_report_cb(
    uint8_t instance,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t* buffer, uint16_t reqlen
) {
    // Return zero to indicate not supported
    return 0;
}

void tud_hid_set_report_cb(
    uint8_t instance,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t const* buffer,
    uint16_t bufsize
) {

}

//callback for sending reports
void tud_hid_report_complete_cb(
    uint8_t instance,
    uint8_t const* report,
    uint16_t len
) {
    led_blink_flag = true;
}