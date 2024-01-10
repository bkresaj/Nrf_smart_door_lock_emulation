#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "nfc_t4t_lib.h"

class MockNfcT4tLib : public SingletonTemplate<MockNfcT4tLib>
{
   public:
    MOCK_METHOD(int, nfc_t4t_setup, (nfc_t4t_callback_t callback, void *context), ());
    MOCK_METHOD(int, nfc_t4t_ndef_rwpayload_set, (uint8_t * emulation_buffer, size_t buffer_length), ());
    MOCK_METHOD(int, nfc_t4t_emulation_start, (), ());
};