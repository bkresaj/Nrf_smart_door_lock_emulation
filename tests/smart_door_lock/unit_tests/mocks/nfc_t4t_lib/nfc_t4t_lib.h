#ifndef NFC_T4T_LIB_H__
#define NFC_T4T_LIB_H__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define NFC_T4T_MAX_PAYLOAD_SIZE 0xFFF0U
#define CONFIG_NDEF_FILE_SIZE 1024

#define ARG_UNUSED(x) (void)(x)

    /**< @brief Emulation mode. */
    typedef enum
    {
        NFC_T4T_EMUMODE_NDEF, /**< Emulated NDEF AID and EF-Files. */
        NFC_T4T_EMUMODE_PICC  /**< Run just ISO-DEP, deliver I-Frames up. */
    } nfc_t4t_emu_mode_t;

    /**< @brief Event identifiers used by the @ref nfc_t4t_callback_t */
    typedef enum
    {
        NFC_T4T_EVENT_NONE,
        /**< This ID is never used. Dummy value for completeness. */

        NFC_T4T_EVENT_FIELD_ON,
        /**< External Reader polling detected. */

        NFC_T4T_EVENT_FIELD_OFF,
        /**< External Reader polling ended. */

        NFC_T4T_EVENT_NDEF_READ,
        /**< External Reader has read static NDEF-Data from Emulation. */
        /**<
         * A Read operation happened on last byte of NDEF-Data.
         */

        NFC_T4T_EVENT_NDEF_UPDATED,
        /**< External Reader has written to length information of NDEF-Data from
         *   Emulation.
         */
        /**<
         * The usual behavior of a Reader-Writer that accesses NDEF information
         * for update is to set the length to zero at the beginning of the
         * update process. It then writes the content of NDEF-Data. When all
         * content is written it will update the length information inside the
         * NDEF file. This event will be generated every time an update to the
         * length is happening. This length information is residing in the first
         * 2 bytes of the NDEF-Content container and is called 'NLEN'. Since
         * this callback is triggered on any access to these bytes  the returned
         * data_length information might not be consistent (e.g. in case of only
         * a single byte write to the length).
         *
         * @param data Pointer to current data of NDEF message
         * @param data_length Current value of NDEF content length information
         * i.e. 'NLEN' field.
         */

        NFC_T4T_EVENT_DATA_TRANSMITTED,
        /**< In Raw mode it signals that the data from @ref
         *     nfc_t4t_response_pdu_send have been sent out.
         */

        NFC_T4T_EVENT_DATA_IND,
        /**< In Raw mode delivers the APDU fragments */
        /**<
         * All @ref NFC_T4T_EVENT_DATA_IND events that have  the @ref
         * NFC_T4T_DI_FLAG_MORE flag set belong to the same APDU. The first
         * @ref NFC_T4T_EVENT_DATA_IND without @ref NFC_T4T_DI_FLAG_MORE
         * flag signals the completeness of the APDU. The Application then has
         * to reply with a call to @ref nfc_t4t_response_pdu_send. The library
         * will handle internally the fragmentation of the response towards the
         * Reader-Writer. The data of the response PDU must be kept valid until
         * the next callback from the library happens (e.g. next @ref
         * NFC_T4T_EVENT_DATA_IND or @ref NFC_T4T_EVENT_FIELD_OFF).
         *
         * @param data Pointer to the fragment of APDU.
         * @param data_length Length of data.
         * @param flags @ref nfc_t4t_data_ind_flags.
         */
    } nfc_t4t_event_t;

    /**< @brief Flags coming with nfc_t4t_callback_t at @ref
     *   NFC_T4T_EVENT_DATA_IND event.
     */
    typedef enum
    {
        NFC_T4T_DI_FLAG_NONE = 0x00, /**< Dummy value. */
        NFC_T4T_DI_FLAG_MORE = 0x01
        /**< This signals that more data is expected to be received. */
    } nfc_t4t_data_ind_flags_t;

    typedef enum
    {
        NFC_T4T_PARAM_FWI,
        /**< Frame Wait Time parameter */

        NFC_T4T_PARAM_FDT_MIN,
        /**< Frame Delay Time Min parameter
         *   The parameter controls the frame transmission timing during collision resolution.
         */

        NFC_T4T_PARAM_SELRES,
        /**< Parameter for setting 'Protocol' bits for SEL_RES packet */

        NFC_T4T_PARAM_NFCID1,
        /**< NFCID1 value, data can be 4, 7, or 10 bytes long  (single, double,
         *   or triple size). To use default NFCID1 of specific length pass one
         *   byte containing requested length. Default 7-byte NFCID1 will be
         *   used if this parameter was not set. This parameter can be set
         *   before nfc_t2t_setup() to set initial NFCID1 and it can be changed
         *   later.
         */
    } nfc_t4t_param_id_t;

    typedef void (*nfc_t4t_callback_t)(void *context, nfc_t4t_event_t event, const uint8_t *data, size_t data_length,
                                       uint32_t flags);

    int nfc_t4t_setup(nfc_t4t_callback_t callback, void *context);
    int nfc_t4t_ndef_rwpayload_set(uint8_t *emulation_buffer, size_t buffer_length);
    int nfc_t4t_emulation_start(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /** NFC_T4T_LIB_H__ */