#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>

#include "nfc/ndef/uri_msg.h"
#include "nfc/t4t/ndef_file.h"

class MockSubsysNfc : public SingletonTemplate<MockSubsysNfc>
{
   public:
    MOCK_METHOD(int, nfc_ndef_uri_msg_encode,
                (enum nfc_ndef_uri_rec_id uri_id_code, uint8_t const *const uri_data, uint16_t uri_data_len,
                 uint8_t *buf, uint32_t *len),
                ());
    MOCK_METHOD(int, nfc_t4t_ndef_file_encode, (uint8_t * file_buf, uint32_t *size), ());
};
