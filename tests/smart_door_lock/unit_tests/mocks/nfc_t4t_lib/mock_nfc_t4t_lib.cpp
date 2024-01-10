#include "mock_nfc_t4t_lib.h"

int nfc_t4t_setup(nfc_t4t_callback_t callback, void *context)
{
    return MockNfcT4tLib::getInstance().nfc_t4t_setup(callback, context);
}

int nfc_t4t_ndef_rwpayload_set(uint8_t *emulation_buffer, size_t buffer_length)
{
    return MockNfcT4tLib::getInstance().nfc_t4t_ndef_rwpayload_set(emulation_buffer, buffer_length);
}

int nfc_t4t_emulation_start()
{
    return MockNfcT4tLib::getInstance().nfc_t4t_emulation_start();
}