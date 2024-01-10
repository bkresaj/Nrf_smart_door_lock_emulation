/**
 * @file nfc.h
 * @brief NFC Type 4 Tag Functions
 *
 * This file provides functions for NFC Type 4 Tag (NFC Forum Type 4 Tag) initialization
 * and NDEF (Near Field Communication Data Exchange Format) message creation.
 */

#ifndef _NFC_H_
#define _NFC_H_

#include <zephyr/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initialize NFC Type 4 Tag (NFC Forum Type 4 Tag).
     *
     * This function initializes the NFC Type 4 Tag functionality, enabling the device to
     * behave as an NFC Forum Type 4 Tag. It must be called before any other NFC Type 4 Tag
     * operations.
     *
     * @return 0 on success, or a negative error code on failure.
     */
    int nfc_t4t_init();

    /**
     * @brief Create a default NDEF (Near Field Communication Data Exchange Format) message.
     *
     * This function generates a default NDEF message suitable for NFC Type 4 Tag emulation.
     * The message is stored in the provided data buffer, and the size of the generated
     * message is updated in the 'size' parameter.
     *
     * @param[out] buff Pointer to the data buffer where the default NDEF message will be
     * stored.
     * @param[in] size The maximum size (in bytes) of data to store.
     * @return 0 on success, or a negative error code on failure.
     */
    int create_ndef_default_message(uint8_t *buff, uint32_t *size);

#ifdef __cplusplus
}
#endif

#endif /* _NFC_H_ */