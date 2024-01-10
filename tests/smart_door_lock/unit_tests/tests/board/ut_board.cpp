#include <gtest/gtest.h>
#include <mock_dk_buttons_and_leds.h>

#include "board.h"

using namespace testing;

class UtBoard : public ::Test
{
   public:
    StrictMock<MockDkButtonsAndLeds> mock_dk_buttons_and_leds;
};

TEST_F(UtBoard, board_init_success)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_leds_init()).WillOnce(Return(0));

    EXPECT_EQ(0, board_init());
}

TEST_F(UtBoard, turn_led_on_fail_when_led_number_is_incorrect)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_led_on(_)).Times(0);

    EXPECT_EQ(-1, turn_led_on(0));
}

TEST_F(UtBoard, turn_led_on_fail_when_dk_set_led_on_fails)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_led_on(_)).WillOnce(Return(-1));

    EXPECT_EQ(-1, turn_led_on(1));
}

TEST_F(UtBoard, turn_led_on_success)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_led_on(_)).WillOnce(Return(0));

    EXPECT_EQ(0, turn_led_on(1));
}

TEST_F(UtBoard, turn_led_off_fail_when_led_number_is_incorrect)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_led_off(_)).Times(0);

    EXPECT_EQ(-1, turn_led_off(0));
}

TEST_F(UtBoard, turn_led_off_fail_when_dk_set_led_off_fails)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_led_off(_)).WillOnce(Return(-1));

    EXPECT_EQ(-1, turn_led_off(1));
}

TEST_F(UtBoard, turn_led_off_success)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_led_off(_)).WillOnce(Return(0));

    EXPECT_EQ(0, turn_led_off(1));
}

TEST_F(UtBoard, turn_all_leds_on_success)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_leds(_)).WillOnce(Return(0));

    EXPECT_EQ(0, turn_all_leds_on());
}

TEST_F(UtBoard, turn_all_leds_off_success)
{
    EXPECT_CALL(mock_dk_buttons_and_leds, dk_set_leds(_)).WillOnce(Return(0));

    EXPECT_EQ(0, turn_all_leds_off());
}
