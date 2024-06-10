# PicoW-Macro-Keyboard
Macro keyboard for windows computers. BUTTON1 (default pin 21) executes `LEFTCTRL + LEFTGUI (Windows key) + ARROW_LEFT` to shift to previous desktop. BUTTON2 (default pin 20) executes `LEFTCTRL + LEFTGUI (Windows key) + ARROW RIGHT` to shift to next desktop. Pico-W's onboard LED will flash on keyboard state change.

Button pins can be changed in ***config.h***.

Libraries used: [Pico-SDK](https://github.com/raspberrypi/pico-sdk), [TinyUSB](https://github.com/raspberrypi/tinyusb/tree/pico) (included with Pico-SDK)

## To build:
1. Ensure you have the [Pico-SDK](https://github.com/raspberrypi/pico-sdk) and relevant environment variables set up
2. Clone the repository: `git clone https://github.com/Tidyrice/PicoW-Macro-Keyboard.git`
3. From the repository root, run `mkdir build` to create a build directory
4. From the build directory, run `cmake ..`. Wait for the makefiles to generate
5. Run `make` or `nmake`. Wait for the build to complete
6. The ***keyboard.uf2*** file in the build folder is ready to flash onto the Pico-W

## Known issues:
1. **BUTTON BOUNCING**. Even with hardware debouncing (RC circuit), Pico-W sometimes detects multiple rising/falling edges in a row. This can cause the LEFTCTRL and LEFTGUI keys to remain on, even after button is released. Introducing button states has minimized this issue as stuck buttons can be fixed by pressing the button again (similar to how on a real keyboard you can oftentimes press a jammed key to unjam it). The only permanent solution is to get better buttons.

## Demo:
<img src="https://github.com/Tidyrice/PicoW-Macro-Keyboard/assets/75756358/29383e97-6510-40b6-a4b1-8d0fa8ab89b9" width="720">
<img src="https://github.com/Tidyrice/PicoW-Macro-Keyboard/assets/75756358/ea80f009-1fc2-4f3b-9d10-4edc7575fe7e" width="720">
