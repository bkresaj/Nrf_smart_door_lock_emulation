#ifndef NDEF_FILE_H_
#define NDEF_FILE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define NFC_NDEF_FILE_NLEN_FIELD_SIZE 2U

#define nfc_t4t_ndef_file_msg_size_get(_file_buf_size) ((_file_buf_size)-NFC_NDEF_FILE_NLEN_FIELD_SIZE)

#define nfc_t4t_ndef_file_msg_get(_file_buf) ((uint8_t *)((_file_buf) + NFC_NDEF_FILE_NLEN_FIELD_SIZE))

    int nfc_t4t_ndef_file_encode(uint8_t *file_buf, uint32_t *size);

#ifdef __cplusplus
}
#endif

#endif