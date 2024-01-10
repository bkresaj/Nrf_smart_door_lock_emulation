#include "board.h"

#include <dk_buttons_and_leds.h>
#include <zephyr/sys/printk.h>

int board_init(void)
{
    int err;

    err = dk_leds_init();
    if (err)
    {
        printk("Cannot init LEDs (err: %d)\n", err);
    }

    return err;
}

int turn_led_on(int led_number)
{
    if (led_number > 0 && led_number < 5)
    {
        int err;

        switch (led_number)
        {
            case 1:
                err = dk_set_led_on(DK_LED1);
                break;
            case 2:
                err = dk_set_led_on(DK_LED2);
                break;
            case 3:
                err = dk_set_led_on(DK_LED3);
                break;
            case 4:
                err = dk_set_led_on(DK_LED4);
                break;

            default:
                err = -1;
                break;
        }
        return err;
    }
    printk("Invalid led number for turning on led\n");
    return -1;
}

// cppcheck-suppress unusedFunction
int turn_led_off(int led_number)
{
    if (led_number > 0 && led_number < 5)
    {
        int err;

        switch (led_number)
        {
            case 1:
                err = dk_set_led_off(DK_LED1);
                break;
            case 2:
                err = dk_set_led_off(DK_LED2);
                break;
            case 3:
                err = dk_set_led_off(DK_LED3);
                break;
            case 4:
                err = dk_set_led_off(DK_LED4);
                break;

            default:
                err = -1;
                break;
        }
        return err;
    }
    printk("Invalid led number for turning off led\n");
    return -1;
}

// cppcheck-suppress unusedFunction
int turn_all_leds_on()
{
    return dk_set_leds(DK_ALL_LEDS_MSK);
}

int turn_all_leds_off()
{
    return dk_set_leds(DK_NO_LEDS_MSK);
}