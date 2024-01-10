#include "littlefs_file_system.h"

#include <nfc.h>
#include <zephyr/fs/fs.h>
#include <zephyr/fs/littlefs.h>

#define STORAGE_PARTITION_LABEL storage_partition
#define STORAGE_PARTITION_ID FIXED_PARTITION_ID(STORAGE_PARTITION_LABEL)

FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(cstorage);
static struct fs_mount_t littlefs_mnt = {
    .type = FS_LITTLEFS, .fs_data = &cstorage, .storage_dev = (void *)STORAGE_PARTITION_ID, .mnt_point = "/lfs1"};

static struct k_mutex fs_mutex;

#define MUTEX_LOCK_TIMEOUT 5000
#define MAX_PATH_LEN 100

int littlefs_file_system_init(void)
{
    int rc;

    rc = fs_mount(&littlefs_mnt);
    if (rc < 0)
    {
        printk("Unsuccessful file system mounting");
        return rc;
    }

    rc = k_mutex_init(&fs_mutex);

    if (rc != 0)
    {
        printk("Cannot initialize mutex!\n");
    }

    return rc;
}

int littlefs_file_write(uint8_t const *buff, uint32_t size, const char *file_name)
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

    if (file_name == NULL)
    {
        printk("File name is null pointer!\n");
        return -1;
    }

    int err;

    err = k_mutex_lock(&fs_mutex, K_MSEC(MUTEX_LOCK_TIMEOUT));

    if (err != 0)
    {
        printk("Cannot acquire mutex, file write failed!\n");
        return err;
    }

    struct fs_file_t file;

    char fname1[MAX_PATH_LEN];

    snprintf(fname1, MAX_PATH_LEN, "%s/%s", littlefs_mnt.mnt_point, file_name);

    fs_file_t_init(&file);
    err = fs_open(&file, fname1, FS_O_CREATE | FS_O_RDWR);
    if (err < 0)
    {
        printk("FAIL: open %s: %d", fname1, err);
        k_mutex_unlock(&fs_mutex);
        return err;
    }

    err = fs_seek(&file, 0, FS_SEEK_SET);
    if (err < 0)
    {
        printk("FAIL: seek %s: %d", fname1, err);
        fs_close(&file);
        k_mutex_unlock(&fs_mutex);
        return err;
    }

    err = fs_write(&file, buff, size);
    if (err < 0)
    {
        printk("FAIL: write %s: %d", fname1, err);
        fs_close(&file);
        k_mutex_unlock(&fs_mutex);
        return err;
    }

    printk("Data was successfully written\n");

    fs_close(&file);

    k_mutex_unlock(&fs_mutex);

    return err;
}

int littlefs_file_read(uint8_t *buff, uint32_t size, const char *file_name)
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

    if (file_name == NULL)
    {
        printk("File name is null pointer!\n");
        return -1;
    }

    int err;

    err = k_mutex_lock(&fs_mutex, K_MSEC(MUTEX_LOCK_TIMEOUT));

    if (err != 0)
    {
        printk("Cannot acquire mutex, file read failed!\n");
        return err;
    }

    struct fs_file_t file;

    char fname1[MAX_PATH_LEN];

    snprintf(fname1, sizeof(fname1), "%s/%s", littlefs_mnt.mnt_point, file_name);

    fs_file_t_init(&file);
    err = fs_open(&file, fname1, FS_O_CREATE | FS_O_RDWR);
    if (err < 0)
    {
        printk("FAIL: open %s: %d", fname1, err);
        k_mutex_unlock(&fs_mutex);
        return err;
    }

    err = fs_read(&file, buff, size);
    if (err < 0)
    {
        printk("FAIL: read %s: [rd:%d]", file_name, err);
        fs_close(&file);
        k_mutex_unlock(&fs_mutex);
        return err;
    }

    printk("Data was successfully read\n");

    fs_close(&file);

    k_mutex_unlock(&fs_mutex);

    return err;
}

int littlefs_ndef_restore_default_message(uint8_t *buff, uint32_t size)
{
    int err;

    err = create_ndef_default_message(buff, &size);
    if (err < 0)
    {
        printk("Cannot create default message!\n");
        return err;
    }

    err = littlefs_file_write(buff, size, "ndef_default_message");
    if (err < 0)
    {
        printk("Cannot flash NDEF message!\n");
    }

    return err;
}
