#include <board.h>
#include <file_system.h>
#include <nfc.h>
#include <zephyr/kernel.h>
#include <zephyr/stats/stats.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/reboot.h>
#include <zephyr/usb/usb_device.h>

#include "file_system.h"

/**
 * @brief The main function of the application.
 *
 * This is the entry point of the application. It initializes the system, sets up
 * various components, and enters the main application loop.
 *
 * @return An integer status code, typically 0 to indicate successful execution.
 */
int main(void)
{
    printk("Starting Nordic NFC Writable NDEF Message example\n");

    int err;

    err = file_system_init();

    if (err != 0)
    {
        printk("Cannot initialize file system!\n");
        printk("Restarting the board!\n");
        sys_reboot(SYS_REBOOT_COLD);
    }

    if (board_init() < 0)
    {
        printk("Cannot initialize board!\n");
        printk("Restarting the board!\n");
        sys_reboot(SYS_REBOOT_COLD);
    }

    if (nfc_t4t_init() < 0)
    {
        printk("Cannot initialize NFC t4t!\n");
        printk("Restarting the board!\n");
        sys_reboot(SYS_REBOOT_COLD);
    }

    while (1)
    {
        k_sleep(K_MSEC(5000));
        printk("While loop :)\n");
    }
    return 0;
}
