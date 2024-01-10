/**
 * @file board.h
 * @brief LED Control Functions
 *
 * This file contains functions for initializing and controlling LEDs on the
 * board. It provides a simple interface for turning individual LEDs on or off,
 * as well as functions for initializing the LED hardware.
 *
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initialize the board.
     *
     * This function initializes leds.
     *
     * @return 0 on success, or a negative error code on failure.
     */
    int board_init();

    /**
     * @brief Turn on a specific LED.
     *
     * This function turns on the LED specified by the LED number.
     *
     * @param led_number The number of the LED to turn on.
     * @return 0 on success, or -1 on failure.
     */
    int turn_led_on(int led_number);

    /**
     * @brief Turn off a specific LED.
     *
     * This function turns off the LED specified by the LED number.
     *
     * @param led_number The number of the LED to turn off.
     * @return 0 on success, or -1 on failure..
     */
    int turn_led_off(int led_number);

    /**
     * @brief Turn on all LEDs.
     *
     * This function turns on all available LEDs on the board.
     *
     * @return 0 on success, or a negative error code on failure.
     */
    int turn_all_leds_on();

    /**
     * @brief Turn off all LEDs.
     *
     * This function turns off all available LEDs on the board.
     *
     * @return 0 on success, or a negative error code on failure.
     */
    int turn_all_leds_off();

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */