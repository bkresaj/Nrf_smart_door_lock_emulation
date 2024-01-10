#include "nvs_file_system.h"

#include <nfc.h>
#include <stdlib.h>
#include <zephyr/fs/nvs.h>
#include <zephyr/storage/flash_map.h>

#define NVS_FLASH_DEVICE FIXED_PARTITION_DEVICE(storage_partition)
#define NVS_SECTOR_SIZE (DT_PROP(DT_CHOSEN(zephyr_flash), erase_block_size))
#define NVS_SECTOR_COUNT 2
#define NVS_STORAGE_OFFSET FIXED_PARTITION_OFFSET(storage_partition)

#define MUTEX_LOCK_TIMEOUT 5000

static struct nvs_fs fs = {
    .sector_size = NVS_SECTOR_SIZE,
    .sector_count = NVS_SECTOR_COUNT,
    .offset = NVS_STORAGE_OFFSET,
};
static struct k_mutex nvs_mutex;

int nvs_file_system_init(void)
{
    int err;

    fs.flash_device = NVS_FLASH_DEVICE;
    if (fs.flash_device == NULL)
    {
        return -ENODEV;
    }

    err = nvs_mount(&fs);
    if (err < 0)
    {
        printk("Cannot initialize NVS!\n");
        return err;
    }

    err = k_mutex_init(&nvs_mutex);

    if (err != 0)
    {
        printk("Cannot initialize mutex!\n");
    }

    return err;
}

int nvs_file_write(uint8_t const *buff, uint32_t size, const char *file_name)
{
    if (buff == NULL)
    {
        printk("Buffer is null pointer!\n");
        return -1;
    }

    if (size == 0)
    {
        printk("Size is 0!\n");
        return -1;
    }

    int file_id = atoi(file_name);

    if (file_id > 10 || file_id < 1)
    {
        printk("Wrong file id!\n");
        return -1;
    }

    int err;

    err = k_mutex_lock(&nvs_mutex, K_MSEC(MUTEX_LOCK_TIMEOUT));

    if (err != 0)
    {
        printk("Cannot acquire mutex, file write failed!\n");
        return err;
    }

    err = nvs_write(&fs, file_id, buff, size);

    k_mutex_unlock(&nvs_mutex);

    return err;
}

int nvs_file_read(uint8_t *buff, uint32_t size, const char *file_name)
{
    if (buff == NULL)
    {
        printk("Buffer is null pointer!\n");
        return -1;
    }

    if (size == 0)
    {
        printk("Size is 0!\n");
        return -1;
    }

    int file_id = atoi(file_name);

    if (file_id > 10 || file_id < 1)
    {
        return -1;
    }

    int err;

    err = k_mutex_lock(&nvs_mutex, K_MSEC(MUTEX_LOCK_TIMEOUT));

    if (err != 0)
    {
        printk("Cannot acquire mutex, file read failed!\n");
        return err;
    }

    err = nvs_read(&fs, file_id, buff, size);
    if (err > 0)
    {
        printk("Found file.\n");
    }
    else
    {
        printk("File not found.\n");
    }

    k_mutex_unlock(&nvs_mutex);

    return err;
}

int nvs_ndef_restore_default_message(uint8_t *buff, uint32_t size)
{
    int err;

    err = create_ndef_default_message(buff, &size);
    if (err < 0)
    {
        printk("Cannot create default message!\n");
        return err;
    }

    err = nvs_file_write(buff, size, FLASH_URL_ADDRESS_ID);
    if (err < 0)
    {
        printk("Cannot flash NDEF message!\n");
    }
    return err;
}