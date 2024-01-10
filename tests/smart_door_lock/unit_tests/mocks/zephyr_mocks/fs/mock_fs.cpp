#include "mock_fs.h"

int fs_mount(struct fs_mount_t *mp)
{
    return MockFs::getInstance().fs_mount(mp);
}

void fs_file_t_init(struct fs_file_t *zfp)
{
    return MockFs::getInstance().fs_file_t_init(zfp);
}

int fs_open(struct fs_file_t *zfp, const char *file_name, fs_mode_t flags)
{
    return MockFs::getInstance().fs_open(zfp, file_name, flags);
}

int fs_close(struct fs_file_t *zfp)
{
    return MockFs::getInstance().fs_close(zfp);
}

int fs_seek(struct fs_file_t *zfp, off_t offset, int whence)
{
    return MockFs::getInstance().fs_seek(zfp, offset, whence);
}

ssize_t fs_write(struct fs_file_t *zfp, const void *ptr, size_t size)
{
    return MockFs::getInstance().fs_write(zfp, ptr, size);
}

ssize_t fs_read(struct fs_file_t *zfp, void *ptr, size_t size)
{
    return MockFs::getInstance().fs_read(zfp, ptr, size);
}
