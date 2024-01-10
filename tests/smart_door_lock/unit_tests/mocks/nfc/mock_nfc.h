#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "nfc.h"

class MockNfc : public SingletonTemplate<MockNfc>
{
   public:
    MOCK_METHOD(int, nfc_t4t_init, (), ());
    MOCK_METHOD(int, create_ndef_default_message, (uint8_t * buff, uint32_t *size), ());
};
