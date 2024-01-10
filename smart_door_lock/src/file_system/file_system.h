/**
 * @file file_system.h
 * @brief File System Interface
 *
 * This file provides an interface for interacting with the file system,
 * including initialization, reading, and writing files.
 */

#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <zephyr/types.h>

    /**
     * @brief Initialize the file system.
     *
     * This function initializes the file system, preparing it for file read and
     * write operations. It must be called before any file operations are performed.
     *
     * @return 0 on success, or a negative error code on failure.
     */
    int file_system_init();

    /**
     * @brief Write data to a file.
     *
     * This function writes the provided data to the specified file. The file is
     * identified by its name. If the file does not exist, it will be created.
     *
     * @param[in] buff Pointer to the data buffer to be written.
     * @param[in] size The size (in bytes) of the data to be written.
     * @param[in] file_name The name of the file to which data will be written.
     * @return The number of bytes written from the buffer on success, or a negative
     * error code on failure.
     */
    int file_write(uint8_t const *buff, uint32_t size, const char *file_name);

    /**
     * @brief Read data from a file.
     *
     * This function reads data from the specified file into the provided data
     * buffer. The file is identified by its name.
     *
     * @param[out] buff Pointer to the data buffer where data will be stored.
     * @param[in] size The maximum size (in bytes) of data to read.
     * @param[in] file_name The name of the file from which data will be read.
     * @return The number of bytes read on success, or a negative error code on
     * failure.
     */
    int file_read(uint8_t *buff, uint32_t size, const char *file_name);

    /**
     * @brief Restore the default NDEF message.
     *
     * This function restores the default Near Field Communication (NFC) Data
     * Exchange Format (NDEF) message to a provided data buffer. The buffer should
     * have sufficient space to hold the default message.
     *
     * @param[out] buff Pointer to the data buffer where the default NDEF message
     * will be stored.
     * @param[in] size The maximum size (in bytes) of the NDEF message.
     * @return The number of bytes written to the buffer on success, or a negative
     * error code on failure.
     */
    int ndef_restore_default_message(uint8_t *buff, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* FILE_SYSTEM_H_ */