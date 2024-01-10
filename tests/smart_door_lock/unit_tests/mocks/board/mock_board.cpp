#include "mock_board.h"

int board_init()
{
    return MockBoard::getInstance().board_init();
}

int turn_led_on(int led_number)
{
    return MockBoard::getInstance().turn_led_on(led_number);
}

int turn_led_off(int led_number)
{
    return MockBoard::getInstance().turn_led_off(led_number);
}

int turn_all_leds_on()
{
    return MockBoard::getInstance().turn_all_leds_on();
}

int turn_all_leds_off()
{
    return MockBoard::getInstance().turn_all_leds_off();
}
