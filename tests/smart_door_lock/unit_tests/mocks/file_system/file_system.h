#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <zephyr/types.h>

    int file_system_init();
    int file_write(uint8_t const *buff, uint32_t size, const char *file_name);
    int file_read(uint8_t *buff, uint32_t size, const char *file_name);
    int ndef_restore_default_message(uint8_t *buff, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif  // FILE_SYSTEM_H_