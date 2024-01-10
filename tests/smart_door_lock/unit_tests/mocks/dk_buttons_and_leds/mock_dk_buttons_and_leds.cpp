#include "mock_dk_buttons_and_leds.h"

int dk_leds_init()
{
    return MockDkButtonsAndLeds::getInstance().dk_leds_init();
}

int dk_set_led_on(uint8_t led_idx)
{
    return MockDkButtonsAndLeds::getInstance().dk_set_led_on(led_idx);
}

int dk_set_led_off(uint8_t led_idx)
{
    return MockDkButtonsAndLeds::getInstance().dk_set_led_off(led_idx);
}

int dk_set_leds(uint32_t leds)
{
    return MockDkButtonsAndLeds::getInstance().dk_set_leds(leds);
}