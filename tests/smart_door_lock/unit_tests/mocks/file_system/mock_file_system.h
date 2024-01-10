#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "file_system.h"

class MockFileSystem : public SingletonTemplate<MockFileSystem>
{
   public:
    MOCK_METHOD(int, file_system_init, (), ());
    MOCK_METHOD(int, file_write, (uint8_t const *buff, uint32_t size, const char *file_name), ());
    MOCK_METHOD(int, file_read, (uint8_t * buff, uint32_t size, const char *file_name), ());
    MOCK_METHOD(int, ndef_restore_default_message, (uint8_t * buff, uint32_t size), ());
};
