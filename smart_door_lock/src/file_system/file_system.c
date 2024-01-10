#include "file_system.h"

#include "littlefs_file_system.h"
#include "nvs_file_system.h"

typedef int (*FileInitFunc)(void);
typedef int (*FileWriteFunc)(const uint8_t *buff, uint32_t size, const char *file_name);
typedef int (*FileReadFunc)(uint8_t *buff, uint32_t size, const char *file_name);
typedef int (*NdefRestoreFunc)(uint8_t *buff, uint32_t size);

typedef struct FileSystemOperations
{
    FileInitFunc file_system_init;
    FileWriteFunc file_write;
    FileReadFunc file_read;
    NdefRestoreFunc ndef_restore_default_message;
} FileSystemOps;

FileSystemOps file_system;

#define LITTLEFS_FILE_SYSTEM

#ifdef LITTLEFS_FILE_SYSTEM
FileSystemOps file_system = {.file_system_init = &littlefs_file_system_init,
                             .file_write = &littlefs_file_write,
                             .file_read = &littlefs_file_read,
                             .ndef_restore_default_message = &littlefs_ndef_restore_default_message};
#endif

#ifdef NVS_FILE_SYSTEM
FileSystemOps file_system = {.file_system_init = &nvs_file_system_init,
                             .file_write = &nvs_file_write,
                             .file_read = &nvs_file_read,
                             .ndef_restore_default_message = &nvs_ndef_restore_default_message};
#endif

int file_system_init(void)
{
    return file_system.file_system_init();
}

int file_write(uint8_t const *buff, uint32_t size, const char *file_name)
{
    return file_system.file_write(buff, size, file_name);
}

int file_read(uint8_t *buff, uint32_t size, const char *file_name)
{
    return file_system.file_read(buff, size, file_name);
}

int ndef_restore_default_message(uint8_t *buff, uint32_t size)
{
    return file_system.ndef_restore_default_message(buff, size);
}