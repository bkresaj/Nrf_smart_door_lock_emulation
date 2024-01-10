#ifndef URI_REC_H_
#define URI_REC_H_

#ifdef __cplusplus
extern "C"
{
#endif

    enum nfc_ndef_uri_rec_id
    {
        NFC_URI_NONE = 0x00,          /**< No prepending is done. */
        NFC_URI_HTTP_WWW = 0x01,      /**< "http://www." */
        NFC_URI_HTTPS_WWW = 0x02,     /**< "https://www." */
        NFC_URI_HTTP = 0x03,          /**< "http:" */
        NFC_URI_HTTPS = 0x04,         /**< "https:" */
        NFC_URI_TEL = 0x05,           /**< "tel:" */
        NFC_URI_MAILTO = 0x06,        /**< "mailto:" */
        NFC_URI_FTP_ANONYMOUS = 0x07, /**< "ftp://anonymous:anonymous@" */
        NFC_URI_FTP_FTP = 0x08,       /**< "ftp://ftp." */
        NFC_URI_FTPS = 0x09,          /**< "ftps://" */
        NFC_URI_SFTP = 0x0A,          /**< "sftp://" */
        NFC_URI_SMB = 0x0B,           /**< "smb://" */
        NFC_URI_NFS = 0x0C,           /**< "nfs://" */
        NFC_URI_FTP = 0x0D,           /**< "ftp://" */
        NFC_URI_DAV = 0x0E,           /**< "dav://" */
        NFC_URI_NEWS = 0x0F,          /**< "news:" */
        NFC_URI_TELNET = 0x10,        /**< "telnet://" */
        NFC_URI_IMAP = 0x11,          /**< "imap:" */
        NFC_URI_RTSP = 0x12,          /**< "rtsp://" */
        NFC_URI_URN = 0x13,           /**< "urn:" */
        NFC_URI_POP = 0x14,           /**< "pop:" */
        NFC_URI_SIP = 0x15,           /**< "sip:" */
        NFC_URI_SIPS = 0x16,          /**< "sips:" */
        NFC_URI_TFTP = 0x17,          /**< "tftp:" */
        NFC_URI_BTSPP = 0x18,         /**< "btspp://" */
        NFC_URI_BTL2CAP = 0x19,       /**< "btl2cap://" */
        NFC_URI_BTGOEP = 0x1A,        /**< "btgoep://" */
        NFC_URI_TCPOBEX = 0x1B,       /**< "tcpobex://" */
        NFC_URI_IRDAOBEX = 0x1C,      /**< "irdaobex://" */
        NFC_URI_FILE = 0x1D,          /**< "file://" */
        NFC_URI_URN_EPC_ID = 0x1E,    /**< "urn:epc:id:" */
        NFC_URI_URN_EPC_TAG = 0x1F,   /**< "urn:epc:tag:" */
        NFC_URI_URN_EPC_PAT = 0x20,   /**< "urn:epc:pat:" */
        NFC_URI_URN_EPC_RAW = 0x21,   /**< "urn:epc:raw:" */
        NFC_URI_URN_EPC = 0x22,       /**< "urn:epc:" */
        NFC_URI_URN_NFC = 0x23,       /**< "urn:nfc:" */
        NFC_URI_RFU = 0xFF            /**< No prepending is done. Reserved for
                                       *   future use.
                                       */
    };

#ifdef __cplusplus
}
#endif

#endif