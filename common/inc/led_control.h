#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "pico/stdlib.h"

extern volatile bool led_blink_flag;
extern uint32_t led_blink_end_time;

void check_handle_led_blink();

#endif