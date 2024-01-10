#include <gtest/gtest.h>
#include <mock_nfc.h>
#include <mock_nvs.h>
#include <mock_subsys_nfc.h>
#include <mock_zephyr_kernel.h>
#include <nfc/t4t/ndef_file.h>
#include <zephyr/device.h>
#include <zephyr/storage/flash_map.h>

#include "nvs_file_system.h"

using namespace testing;

class UtNvsFileSystem : public ::Test
{
   public:
    StrictMock<MockNvs> mock_nvs;
    StrictMock<MockZephyrKernel> mock_zephyr_kernel;
    StrictMock<MockSubsysNfc> mock_subsys_nfc;
    StrictMock<MockNfc> mock_nfc;

    void nvs_file_system_init_success_expectations()
    {
        EXPECT_CALL(mock_nvs, nvs_mount(_)).WillOnce(Return(0));
        EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(0));
        EXPECT_EQ(0, nvs_file_system_init());
    }

    void nvs_file_write_success_expectations()
    {
        EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
        EXPECT_CALL(mock_nvs, nvs_write(_, _, _, _)).WillOnce(Return(0));
        EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);
    }
};

TEST_F(UtNvsFileSystem, nvs_file_system_init_fails_when_nvs_mount_fails)
{
    InSequence s;

    EXPECT_CALL(mock_nvs, nvs_mount(_)).WillOnce(Return(-1));

    EXPECT_NE(0, nvs_file_system_init());
}

TEST_F(UtNvsFileSystem, nvs_file_system_init_fails_when_k_mutex_init_fails)
{
    InSequence s;

    EXPECT_CALL(mock_nvs, nvs_mount(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(-1));

    EXPECT_NE(0, nvs_file_system_init());
}

TEST_F(UtNvsFileSystem, nvs_file_system_init_success)
{
    InSequence s;

    nvs_file_system_init_success_expectations();
}

TEST_F(UtNvsFileSystem, nvs_file_write_fails_when_wrong_id_is_given)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* random_file_id = "15";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_nvs, nvs_write(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_write(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_write_fails_when_buffer_is_null_pointer)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_nvs, nvs_write(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_write(NULL, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_write_fails_when_size_is_zero)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    uint32_t size_of_buffer = 0;
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_nvs, nvs_write(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_write(buffer, size_of_buffer, random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_write_fails_when_k_mutex_lock_fails)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_nvs, nvs_write(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_write(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_write_fails_when_nvs_write_fails)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nvs, nvs_write(_, _, _, _)).WillOnce(Return(EFBIG));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, nvs_file_write(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_write_success)
{
    const uint8_t buffer[] = {'t', 'e', 's', 't'};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    nvs_file_write_success_expectations();

    EXPECT_EQ(0, nvs_file_write(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_read_fails_when_wrong_id_is_given)
{
    uint8_t buffer[10] = {};
    const char* random_file_id = "15";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_nvs, nvs_read(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_read(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_read_fails_when_buffer_is_null_pointer)
{
    uint8_t buffer[10] = {};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_nvs, nvs_read(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_read(NULL, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_read_fails_when_size_of_buffer_is_zero)
{
    uint8_t buffer[10] = {};
    uint32_t buffer_size = 0;
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).Times(0);
    EXPECT_CALL(mock_nvs, nvs_read(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_read(buffer, buffer_size, random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_read_fails_when_k_mutex_lock_fails)
{
    uint8_t buffer[10] = {};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));
    EXPECT_CALL(mock_nvs, nvs_read(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(0);

    EXPECT_NE(0, nvs_file_read(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_read_fails_when_nvs_read_fails)
{
    uint8_t buffer[10] = {};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nvs, nvs_read(_, _, _, _)).WillOnce(Return(ENOENT));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, nvs_file_read(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_file_read_success)
{
    uint8_t buffer[10] = {};
    const char* random_file_id = "1";

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nvs, nvs_read(_, _, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_EQ(0, nvs_file_read(buffer, sizeof(buffer), random_file_id));
}

TEST_F(UtNvsFileSystem, nvs_ndef_restore_default_message_fails_when_create_ndef_default_message_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_nfc, create_ndef_default_message(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, nvs_ndef_restore_default_message(buffer, buffer_size));
}

TEST_F(UtNvsFileSystem, nvs_ndef_restore_default_message_fails_when_file_write_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_nfc, create_ndef_default_message(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, nvs_ndef_restore_default_message(buffer, buffer_size));
}

TEST_F(UtNvsFileSystem, nvs_ndef_restore_default_message_success)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    nvs_file_system_init_success_expectations();

    EXPECT_CALL(mock_nfc, create_ndef_default_message(_, _)).WillOnce(Return(0));

    nvs_file_write_success_expectations();

    EXPECT_EQ(0, nvs_ndef_restore_default_message(buffer, buffer_size));
}
