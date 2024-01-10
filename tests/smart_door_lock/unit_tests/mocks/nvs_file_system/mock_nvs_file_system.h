#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "nvs_file_system.h"

class MockNvsFileSystem : public SingletonTemplate<MockNvsFileSystem>
{
   public:
    MOCK_METHOD(int, nvs_file_system_init, (), ());
    MOCK_METHOD(int, nvs_file_write, (uint8_t const *buff, uint32_t size, const uint8_t file_id), ());
    MOCK_METHOD(int, nvs_file_read, (uint8_t * buff, uint32_t size, const uint8_t file_id), ());
    MOCK_METHOD(int, nvs_ndef_default_message, (uint8_t * buff, uint32_t *size), ());
    MOCK_METHOD(int, nvs_ndef_restore_default_message, (uint8_t * buff, uint32_t size), ());
};