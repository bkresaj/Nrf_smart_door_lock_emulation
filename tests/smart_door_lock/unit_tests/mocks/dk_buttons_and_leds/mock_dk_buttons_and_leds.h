#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "dk_buttons_and_leds.h"

class MockDkButtonsAndLeds : public SingletonTemplate<MockDkButtonsAndLeds>
{
   public:
    MOCK_METHOD(int, dk_leds_init, (), ());
    MOCK_METHOD(int, dk_set_led_on, (uint8_t led_idx), ());
    MOCK_METHOD(int, dk_set_led_off, (uint8_t led_idx), ());
    MOCK_METHOD(int, dk_set_leds, (uint32_t leds), ());
};