#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>
#include <zephyr/types.h>

class MockFs : public SingletonTemplate<MockFs>
{
   public:
    MOCK_METHOD(int, fs_mount, (struct fs_mount_t * mp), ());
    MOCK_METHOD(void, fs_file_t_init, (struct fs_file_t * zfp), ());
    MOCK_METHOD(int, fs_open, (struct fs_file_t * zfp, const char *file_name, fs_mode_t flags), ());
    MOCK_METHOD(int, fs_close, (struct fs_file_t * zfp), ());
    MOCK_METHOD(int, fs_seek, (struct fs_file_t * zfp, off_t offset, int whence), ());
    MOCK_METHOD(ssize_t, fs_write, (struct fs_file_t * zfp, const void *ptr, size_t size), ());
    MOCK_METHOD(ssize_t, fs_read, (struct fs_file_t * zfp, void *ptr, size_t size), ());
};
