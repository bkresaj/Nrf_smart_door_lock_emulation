#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "board.h"

class MockBoard : public SingletonTemplate<MockBoard>
{
   public:
    MOCK_METHOD(int, board_init, (), ());
    MOCK_METHOD(int, turn_led_on, (int led_number), ());
    MOCK_METHOD(int, turn_led_off, (int led_number), ());
    MOCK_METHOD(int, turn_all_leds_on, (), ());
    MOCK_METHOD(int, turn_all_leds_off, (), ());
};