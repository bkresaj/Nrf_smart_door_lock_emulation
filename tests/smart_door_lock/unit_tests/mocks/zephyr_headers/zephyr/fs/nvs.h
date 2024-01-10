#ifndef NVS_H_
#define NVS_H_

#include <stdbool.h>
#include <stdint.h>

#include "../kernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

// random value
#define erase_block_size 1000

    typedef long int off_t;

    struct nvs_fs
    {
        off_t offset;
        uint32_t ate_wra;
        uint32_t data_wra;
        uint16_t sector_size;
        uint16_t sector_count;
        bool ready;
        struct k_mutex nvs_lock;
        const struct device *flash_device;
        const struct flash_parameters *flash_parameters;
#if CONFIG_NVS_LOOKUP_CACHE
        uint32_t lookup_cache[CONFIG_NVS_LOOKUP_CACHE_SIZE];
#endif
    };

    int nvs_mount(struct nvs_fs *fs);
    ssize_t nvs_write(struct nvs_fs *fs, uint16_t id, const void *data, size_t len);
    ssize_t nvs_read(struct nvs_fs *fs, uint16_t id, void *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif