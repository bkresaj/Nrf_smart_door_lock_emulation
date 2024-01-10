#ifndef NFC_H_
#define NFC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <zephyr/types.h>

    int nfc_t4t_init();
    int create_ndef_default_message(uint8_t *buff, uint32_t *size);

#ifdef __cplusplus
}
#endif

#endif /* NFC_H_ */