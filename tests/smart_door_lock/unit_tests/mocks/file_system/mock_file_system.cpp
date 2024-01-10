#include "mock_file_system.h"

int file_system_init()
{
    return MockFileSystem::getInstance().file_system_init();
}

int file_write(uint8_t const *buff, uint32_t size, const char *file_name)
{
    return MockFileSystem::getInstance().file_write(buff, size, file_name);
}

int file_read(uint8_t *buff, uint32_t size, const char *file_name)
{
    return MockFileSystem::getInstance().file_read(buff, size, file_name);
}

int ndef_restore_default_message(uint8_t *buff, uint32_t size)
{
    return MockFileSystem::getInstance().ndef_restore_default_message(buff, size);
}
