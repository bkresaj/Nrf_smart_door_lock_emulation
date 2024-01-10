#ifndef URI_MSG_H_
#define URI_MSG_H_

#include "stdint.h"
#include "uri_rec.h"

#ifdef __cplusplus
extern "C"
{
#endif

    int nfc_ndef_uri_msg_encode(enum nfc_ndef_uri_rec_id uri_id_code, uint8_t const *const uri_data,
                                uint16_t uri_data_len, uint8_t *buf, uint32_t *len);

#ifdef __cplusplus
}
#endif

#endif