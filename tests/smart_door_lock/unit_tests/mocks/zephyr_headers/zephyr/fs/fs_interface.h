#ifndef FS_INTERFACE_H_
#define FS_INTERFACE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* Type for fs_open flags */
    typedef uint8_t fs_mode_t;

    struct fs_mount_t;

    /**
     * @addtogroup file_system_api
     * @{
     */

    /**
     * @brief File object representing an open file
     *
     * The object needs to be initialized with fs_file_t_init().
     */
    struct fs_file_t
    {
        /** Pointer to file object structure */
        void *filep;
        /** Pointer to mount point structure */
        const struct fs_mount_t *mp;
        /** Open/create flags */
        fs_mode_t flags;
    };

#ifdef __cplusplus
}
#endif

#endif