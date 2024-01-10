#include "nfc.h"

#include <board.h>
#include <custom_bluetooth.h>
#include <file_system.h>
#include <nfc/ndef/uri_msg.h>
#include <nfc/t4t/ndef_file.h>
#include <nfc_t4t_lib.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define NFC_FIELD_LED 1
#define NFC_WRITE_LED 2
#define NFC_OPEN_DOOR_LED 3
#define NFC_READ_LED 4

#define DATA_PAYLOAD_IN_NDEF_MESSAGE 9
#define WELCOME_MSG_BUF_LEN CONFIG_NDEF_FILE_SIZE
#define PSWD_MSG_BUF_LEN 7
#define CORRECT_NDEF_MSG_LEN_FOR_CHECKING_PSWD 14
#define BLE_ON_MSG_BUF_LEN 12
#define BLE_OFF_MSG_BUF_LEN 13
#define CORRECT_NDEF_MSG_LEN_FOR_CHECKING_BLE_ON 19
#define CORRECT_NDEF_MSG_LEN_FOR_CHECKING_BLE_OFF 20

static uint8_t welcome_msg_buf[WELCOME_MSG_BUF_LEN];
static uint8_t pswd_msg_buf[PSWD_MSG_BUF_LEN] = {'t', 'e', 's', 't', '1', '2', '3'};
static uint8_t ble_on_msg_buf[BLE_ON_MSG_BUF_LEN] = {'t', 'u', 'r', 'n', 'b', 'l', 'e', 'o', 'n', '1', '2', '3'};
static uint8_t ble_off_msg_buff[BLE_OFF_MSG_BUF_LEN] = {'t', 'u', 'r', 'n', 'b', 'l', 'e',
                                                        'o', 'f', 'f', '1', '2', '3'};

static const uint8_t m_url[] = {'g', 'o', 'o', 'g', 'l', 'e', '.', 'c', 'o', 'm'};

static struct k_mutex nfc_mutex;

#define MUTEX_LOCK_TIMEOUT 5000

static bool check_password()
{
    if (memcmp(pswd_msg_buf, &welcome_msg_buf[DATA_PAYLOAD_IN_NDEF_MESSAGE], PSWD_MSG_BUF_LEN) == 0)
    {
        return true;
    }
    return false;
}

static bool check_ble_on_password()
{
    if (memcmp(ble_on_msg_buf, &welcome_msg_buf[DATA_PAYLOAD_IN_NDEF_MESSAGE], BLE_ON_MSG_BUF_LEN) == 0)
    {
        return true;
    }
    return false;
}

static bool check_ble_off_password()
{
    if (memcmp(ble_off_msg_buff, &welcome_msg_buf[DATA_PAYLOAD_IN_NDEF_MESSAGE], BLE_OFF_MSG_BUF_LEN) == 0)
    {
        return true;
    }
    return false;
}

/**
 * @brief Callback function for handling NFC events.
 */
static void nfc_callback(void *context, nfc_t4t_event_t event, const uint8_t *data, size_t data_length, uint32_t flags)
{
    ARG_UNUSED(context);
    ARG_UNUSED(data);
    ARG_UNUSED(flags);

    switch (event)
    {
        case NFC_T4T_EVENT_FIELD_ON:
            turn_led_on(NFC_FIELD_LED);
            break;

        case NFC_T4T_EVENT_FIELD_OFF:
            turn_all_leds_off();
            break;

        case NFC_T4T_EVENT_NDEF_READ:
            turn_led_on(NFC_READ_LED);
            break;

        case NFC_T4T_EVENT_NDEF_UPDATED:
            turn_led_on(NFC_WRITE_LED);
            if (data_length == CORRECT_NDEF_MSG_LEN_FOR_CHECKING_PSWD)
            {
                if (check_password())
                {
                    turn_led_on(NFC_OPEN_DOOR_LED);
                }
            }
            if (data_length == CORRECT_NDEF_MSG_LEN_FOR_CHECKING_BLE_ON)
            {
                if (check_ble_on_password())
                {
                    start_smp_bluetooth_adverts();
                }
            }
            if (data_length == CORRECT_NDEF_MSG_LEN_FOR_CHECKING_BLE_OFF)
            {
                if (check_ble_off_password())
                {
                    stop_smp_bluetooth_adverts();
                }
            }
            ndef_restore_default_message(welcome_msg_buf, WELCOME_MSG_BUF_LEN);
            break;

        default:
            break;
    }
}

int nfc_t4t_init()
{
    int err;

    err = nfc_t4t_setup(nfc_callback, NULL);

    if (err < 0)
    {
        printk("Cannot setup t4t library!\n");
        return err;
    }

    err = k_mutex_init(&nfc_mutex);

    if (err != 0)
    {
        printk("Cannot initialize mutex!\n");
        return err;
    }

    err = ndef_restore_default_message(welcome_msg_buf, WELCOME_MSG_BUF_LEN);

    if (err < 0)
    {
        printk("Cannot restore default NDEF message!\n");
        return err;
    }

    err = nfc_t4t_ndef_rwpayload_set(welcome_msg_buf, WELCOME_MSG_BUF_LEN);

    if (err < 0)
    {
        printk("Cannot set payload!\n");
        return err;
    }

    err = nfc_t4t_emulation_start();

    if (err < 0)
    {
        printk("Cannot start emulation!\n");
        return err;
    }

    return 0;
}

int create_ndef_default_message(uint8_t *buff, uint32_t *size)
{
    int err = k_mutex_lock(&nfc_mutex, K_MSEC(MUTEX_LOCK_TIMEOUT));

    if (err != 0)
    {
        printk("Cannot acquire mutex, creating default message failed!\n");
        return err;
    }

    uint32_t ndef_size = nfc_t4t_ndef_file_msg_size_get(*size);

    err = nfc_ndef_uri_msg_encode(NFC_URI_HTTP_WWW, m_url, sizeof(m_url), nfc_t4t_ndef_file_msg_get(buff), &ndef_size);

    if (err)
    {
        printk("nfc_ndef_uri_msg_encode failed!\n");
        k_mutex_unlock(&nfc_mutex);
        return err;
    }

    err = nfc_t4t_ndef_file_encode(buff, &ndef_size);

    *size = ndef_size;

    k_mutex_unlock(&nfc_mutex);

    return err;
}
