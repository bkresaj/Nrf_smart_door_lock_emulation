#include "mock_nvs_file_system.h"

int nvs_file_system_init()
{
    return MockNvsFileSystem::getInstance().nvs_file_system_init();
}

int nvs_file_write(uint8_t const *buff, uint32_t size, const uint8_t file_id)
{
    return MockNvsFileSystem::getInstance().nvs_file_write(buff, size, file_id);
}

int nvs_file_read(uint8_t *buff, uint32_t size, const uint8_t file_id)
{
    return MockNvsFileSystem::getInstance().nvs_file_read(buff, size, file_id);
}

int nvs_ndef_default_message(uint8_t *buff, uint32_t *size)
{
    return MockNvsFileSystem::getInstance().nvs_ndef_default_message(buff, size);
}

int nvs_ndef_restore_default_message(uint8_t *buff, uint32_t size)
{
    return MockNvsFileSystem::getInstance().nvs_ndef_restore_default_message(buff, size);
}