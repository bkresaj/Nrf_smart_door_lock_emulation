#ifndef DK_BUTTON_AND_LEDS_H__
#define DK_BUTTON_AND_LEDS_H__

#include <stdint.h>
#include <zephyr/sys/slist.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define BIT(n) (1 << (n))

#define DK_NO_LEDS_MSK (0)
#define DK_LED1 0
#define DK_LED2 1
#define DK_LED3 2
#define DK_LED4 3
#define DK_LED1_MSK BIT(DK_LED1)
#define DK_LED2_MSK BIT(DK_LED2)
#define DK_LED3_MSK BIT(DK_LED3)
#define DK_LED4_MSK BIT(DK_LED4)
#define DK_ALL_LEDS_MSK (DK_LED1_MSK | DK_LED2_MSK | DK_LED3_MSK | DK_LED4_MSK)

#define DK_NO_BTNS_MSK (0)
#define DK_BTN1 0
#define DK_BTN2 1
#define DK_BTN3 2
#define DK_BTN4 3
#define DK_BTN1_MSK BIT(DK_BTN1)
#define DK_BTN2_MSK BIT(DK_BTN2)
#define DK_BTN3_MSK BIT(DK_BTN3)
#define DK_BTN4_MSK BIT(DK_BTN4)
#define DK_ALL_BTNS_MSK (DK_BTN1_MSK | DK_BTN2_MSK | DK_BTN3_MSK | DK_BTN4_MSK)
    typedef void (*button_handler_t)(uint32_t button_state, uint32_t has_changed);

    /** Button handler list entry. */
    struct button_handler
    {
        button_handler_t cb; /**< Callback function. */
        sys_snode_t node;    /**< Linked list node, for internal use. */
    };

    int dk_leds_init();
    int dk_set_led_on(uint8_t led_idx);
    int dk_set_led_off(uint8_t led_idx);
    int dk_set_leds(uint32_t leds);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* DK_BUTTON_AND_LEDS_H__ */