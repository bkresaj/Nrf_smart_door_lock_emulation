/**
 * @file nvs_file_system.h
 * @brief NVS File System Functions
 *
 * This file provides functions for initializing an NVS-based file system, writing data
 * to files, reading data from files, and restoring a default NDEF (Near Field Communication
 * Data Exchange Format) message from NVS storage.
 */

#ifndef NVS_FILE_SYSTEM_H_
#define NVS_FILE_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <zephyr/types.h>

#define FLASH_URL_ADDRESS_ID "1" /**< Address of URL message in FLASH */

    /**
     * @brief Initialize the NVS-based file system.
     *
     * This function initializes the NVS-based file system, allowing the device to store and
     * manage files in non-volatile storage. It must be called before any other NVS file system
     * operations.
     *
     * @return 0 on success, or a negative error code on failure.
     */
    int nvs_file_system_init();

    /**
     * @brief Write data to an NVS file.
     *
     * This function writes data from the provided buffer to an NVS file with the specified
     * file name. The size parameter specifies the number of bytes to write.
     *
     * @param[in] buff Pointer to the data buffer containing the data to be written.
     * @param[in] size The size, in bytes, of the data to be written.
     * @param[in] file_name The name of the NVS file to write data to.
     * @return The number of bytes written to the buffer on success, or a negative
     * error code on failure.
     */
    int nvs_file_write(uint8_t const *buff, uint32_t size, const char *file_name);

    /**
     * @brief Read data from an NVS file.
     *
     * This function reads data from an NVS file with the specified file name into the provided
     * buffer. The size parameter specifies the maximum number of bytes to read.
     *
     * @param[out] buff Pointer to the data buffer where the read data will be stored.
     * @param[in] size The maximum number of bytes to read.
     * @param[in] file_name The name of the NVS file to read data from.
     * @return The number of bytes read on success, or a negative error code on failure.
     */
    int nvs_file_read(uint8_t *buff, uint32_t size, const char *file_name);

    /**
     * @brief Restore a default NDEF message from NVS storage.
     *
     * This function restores a default NDEF message suitable for NFC (Near Field Communication)
     * from NVS storage. The message is stored in the provided data buffer.
     *
     * @param[out] buff Pointer to the data buffer where the default NDEF message will be stored.
     * @param[in] size The maximum size (in bytes) of the NDEF message.
     * @return The number of bytes written to the buffer on success, or a negative error
     * code on failure.
     */
    int nvs_ndef_restore_default_message(uint8_t *buff, uint32_t size);

    /** @} */

#ifdef __cplusplus
}
#endif

#endif /* NVS_FILE_SYSTEM_H_ */