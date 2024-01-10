#ifndef NVS_FILE_SYSTEM_H_
#define NVS_FILE_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <zephyr/types.h>

    int nvs_file_system_init();
    int nvs_file_write(uint8_t const *buff, uint32_t size, const uint8_t file_id);
    int nvs_file_read(uint8_t *buff, uint32_t size, const uint8_t file_id);
    int nvs_ndef_default_message(uint8_t *buff, uint32_t *size);
    int nvs_ndef_restore_default_message(uint8_t *buff, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* NVS_FILE_SYSTEM_H_ */