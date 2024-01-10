#include <gtest/gtest.h>
#include <mock_fs.h>
#include <mock_nfc.h>
#include <mock_zephyr_kernel.h>
#include <zephyr/fs/fs.h>
#include <zephyr/fs/littlefs.h>
#include <zephyr/types.h>

#include "littlefs_file_system.h"

using namespace testing;

class UtLittlefsFileSystem : public ::Test
{
   public:
    StrictMock<MockFs> mock_fs;
    StrictMock<MockZephyrKernel> mock_zephyr_kernel;
    StrictMock<MockNfc> mock_nfc;
};

TEST_F(UtLittlefsFileSystem, littlefs_file_system_init_fails_when_fs_mount_fails)
{
    EXPECT_CALL(mock_fs, fs_mount(_)).WillOnce(Return(-1));

    EXPECT_NE(0, littlefs_file_system_init());
}

TEST_F(UtLittlefsFileSystem, littlefs_file_system_init_fails_when_k_mutex_init_fails)
{
    InSequence s;

    EXPECT_CALL(mock_fs, fs_mount(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(-1));

    EXPECT_NE(0, littlefs_file_system_init());
}

TEST_F(UtLittlefsFileSystem, littlefs_file_system_init_success)
{
    InSequence s;

    EXPECT_CALL(mock_fs, fs_mount(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(0));

    EXPECT_EQ(0, littlefs_file_system_init());
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_buffer_is_null_pointer)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_write(NULL, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_size_is_zero)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    uint32_t size_of_buffer = 0;
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_write(buffer, size_of_buffer, file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_file_name_is_null_pointer)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_write(buffer, sizeof(buffer), NULL));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_k_mutex_lock_fails)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_write(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_file_open_fails)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, littlefs_file_write(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_file_seek_fails)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(1);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, littlefs_file_write(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_fails_when_file_write_fails)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_close(_)).Times(1);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, littlefs_file_write(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_write_success)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_close(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_EQ(0, littlefs_file_write(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_fails_when_buffer_is_null_pointer)
{
    uint8_t buffer[10] = {};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_read(NULL, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_fails_when_size_of_buffer_is_zero)
{
    uint8_t buffer[10] = {};
    uint32_t buffer_size = 0;
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_read(buffer, buffer_size, file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_fails_when_file_name_is_null_pointer)
{
    uint8_t buffer[10] = {};

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_read(buffer, sizeof(buffer), NULL));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_fails_when_k_mutex_lock_fails)
{
    uint8_t buffer[10] = {};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(0);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, littlefs_file_read(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_fails_when_file_open_fails)
{
    uint8_t buffer[10] = {};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).Times(0);
    EXPECT_CALL(mock_fs, fs_close(_)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, littlefs_file_read(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_fails_when_file_read_fails)
{
    uint8_t buffer[10] = {};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_fs, fs_close(_)).Times(1);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, littlefs_file_read(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_file_read_success)
{
    uint8_t buffer[10] = {};
    const char* file_name = "test123";

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_read(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_close(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_EQ(0, littlefs_file_read(buffer, sizeof(buffer), file_name));
}

TEST_F(UtLittlefsFileSystem, littlefs_ndef_restore_default_message_fails_when_create_ndef_default_message_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    EXPECT_CALL(mock_nfc, create_ndef_default_message(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, littlefs_ndef_restore_default_message(buffer, buffer_size));
}

TEST_F(UtLittlefsFileSystem, littlefs_ndef_restore_default_message_fails_when_file_write_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    EXPECT_CALL(mock_nfc, create_ndef_default_message(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, littlefs_ndef_restore_default_message(buffer, buffer_size));
}

TEST_F(UtLittlefsFileSystem, littlefs_ndef_restore_default_message_success)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    EXPECT_CALL(mock_nfc, create_ndef_default_message(_, _)).WillOnce(Return(0));

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_file_t_init(_)).Times(1);
    EXPECT_CALL(mock_fs, fs_open(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_seek(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_write(_, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_fs, fs_close(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_EQ(0, littlefs_ndef_restore_default_message(buffer, buffer_size));
}
