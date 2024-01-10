#ifndef FS_H_
#define FS_H_

#include "../sys/dlist.h"
#include "fs_interface.h"
#include "nvs.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name fs_open open and creation mode flags
 * @{
 */
/** Open for read flag */
#define FS_O_READ 0x01
/** Open for write flag */
#define FS_O_WRITE 0x02
/** Open for read-write flag combination */
#define FS_O_RDWR (FS_O_READ | FS_O_WRITE)
/** Bitmask for read and write flags */
#define FS_O_MODE_MASK 0x03

/** Create file if it does not exist */
#define FS_O_CREATE 0x10
/** Open/create file for append */
#define FS_O_APPEND 0x20
/** Bitmask for open/create flags */
#define FS_O_FLAGS_MASK 0x30

/**
 * @name fs_seek whence parameter values
 * @{
 */
#ifndef FS_SEEK_SET
/** Seek from the beginning of file */
#define FS_SEEK_SET 0
#endif
#ifndef FS_SEEK_CUR
/** Seek from a current position */
#define FS_SEEK_CUR 1
#endif
#ifndef FS_SEEK_END
/** Seek from the end of file */
#define FS_SEEK_END 2
#endif

    enum
    {
        /** Identifier for in-tree FatFS file system. */
        FS_FATFS = 0,

        /** Identifier for in-tree LittleFS file system. */
        FS_LITTLEFS,

        /** Identifier for in-tree Ext2 file system. */
        FS_EXT2,

        /** Base identifier for external file systems. */
        FS_TYPE_EXTERNAL_BASE,
    };

    struct fs_mount_t
    {
        /** Entry for the fs_mount_list list */
        sys_dnode_t node;
        /** File system type */
        int type;
        /** Mount point directory name (ex: "/fatfs") */
        const char *mnt_point;
        /** Pointer to file system specific data */
        void *fs_data;
        /** Pointer to backend storage device */
        void *storage_dev;
        /* The following fields are filled by file system core */
        /** Length of Mount point string */
        size_t mountp_len;
        /** Mount flags */
        uint8_t flags;
    };

    int fs_mount(struct fs_mount_t *mp);
    void fs_file_t_init(struct fs_file_t *zfp);
    int fs_open(struct fs_file_t *zfp, const char *file_name, fs_mode_t flags);
    int fs_close(struct fs_file_t *zfp);
    int fs_seek(struct fs_file_t *zfp, off_t offset, int whence);
    ssize_t fs_write(struct fs_file_t *zfp, const void *ptr, size_t size);
    ssize_t fs_read(struct fs_file_t *zfp, void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif