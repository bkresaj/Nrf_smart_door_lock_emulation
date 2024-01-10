#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C"
{
#endif

    int board_init();
    int turn_led_on(int led_number);
    int turn_led_off(int led_number);
    int turn_all_leds_on();
    int turn_all_leds_off();

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */