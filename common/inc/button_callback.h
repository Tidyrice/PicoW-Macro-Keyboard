#ifndef BUTTON_CALLBACK_H
#define BUTTON_CALLBACK_H

#include "pico/stdlib.h"

/* State management to prevent consecutive rising/falling edges from bricking the keyboard.
Consecutive rising/falling edges likely caused by hardware glitches or electrical noise. */
typedef enum {
    BUTTON_STATE_IDLE,
    BUTTON_STATE_PRESSED
} button_state_t;

extern volatile button_state_t button1_state;
extern volatile button_state_t button2_state;

extern volatile uint32_t last_interrupt_time; //for debouncing

//ISR callback on button press
void button_callback(uint gpio, uint32_t events);

#endif