#include "mock_nfc.h"

int nfc_t4t_init()
{
    return MockNfc::getInstance().nfc_t4t_init();
}

int create_ndef_default_message(uint8_t *buff, uint32_t *size)
{
    return MockNfc::getInstance().create_ndef_default_message(buff, size);
}
