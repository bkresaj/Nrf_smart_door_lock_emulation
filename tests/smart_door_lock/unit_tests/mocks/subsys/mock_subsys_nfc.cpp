#include "mock_subsys_nfc.h"

int nfc_ndef_uri_msg_encode(enum nfc_ndef_uri_rec_id uri_id_code, uint8_t const *const uri_data, uint16_t uri_data_len,
                            uint8_t *buf, uint32_t *len)
{
    return MockSubsysNfc::getInstance().nfc_ndef_uri_msg_encode(uri_id_code, uri_data, uri_data_len, buf, len);
}

int nfc_t4t_ndef_file_encode(uint8_t *file_buf, uint32_t *size)
{
    return MockSubsysNfc::getInstance().nfc_t4t_ndef_file_encode(file_buf, size);
}
