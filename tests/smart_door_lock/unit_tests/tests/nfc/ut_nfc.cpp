#include <custom_bluetooth.h>
#include <gtest/gtest.h>
#include <mock_board.h>
#include <mock_file_system.h>
#include <mock_nfc_t4t_lib.h>
#include <mock_subsys_nfc.h>
#include <mock_zephyr_kernel.h>
#include <nfc/ndef/uri_msg.h>
#include <nfc/t4t/ndef_file.h>

#include "nfc.h"

using namespace testing;

class UtNfc : public ::Test
{
   public:
    StrictMock<MockNfcT4tLib> mock_nfc_t4t_lib;
    StrictMock<MockFileSystem> mock_file_system;
    StrictMock<MockZephyrKernel> mock_zephyr_kernel;
    StrictMock<MockSubsysNfc> mock_subsys_nfc;

    void nvs_ndef_default_message_success_expectations()
    {
        EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
        EXPECT_CALL(mock_subsys_nfc, nfc_ndef_uri_msg_encode(_, _, _, _, _)).WillOnce(Return(0));
        EXPECT_CALL(mock_subsys_nfc, nfc_t4t_ndef_file_encode(_, _)).WillOnce(Return(0));
        EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);
    }
};

TEST_F(UtNfc, nfc_t4t_init_fails_when_nfc_t4t_setup_fails)
{
    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_setup(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, nfc_t4t_init());
}

TEST_F(UtNfc, nfc_t4t_init_fails_when_k_mutex_init_fails)
{
    InSequence s;

    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_setup(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(-1));

    EXPECT_NE(0, nfc_t4t_init());
}

TEST_F(UtNfc, nfc_t4t_init_fails_when_nvs_ndef_restore_default_message_fails)
{
    InSequence s;

    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_setup(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_file_system, ndef_restore_default_message(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, nfc_t4t_init());
}

TEST_F(UtNfc, nfc_t4t_init_fails_when_nfc_t4t_ndef_rwpayload_set_fails)
{
    InSequence s;

    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_setup(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_file_system, ndef_restore_default_message(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_ndef_rwpayload_set(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, nfc_t4t_init());
}

TEST_F(UtNfc, nfc_t4t_init_fails_when_nfc_t4t_emulation_start_fails)
{
    InSequence s;

    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_setup(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_file_system, ndef_restore_default_message(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_ndef_rwpayload_set(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_emulation_start()).WillOnce(Return(-1));

    EXPECT_NE(0, nfc_t4t_init());
}

TEST_F(UtNfc, nfc_t4t_init_success)
{
    InSequence s;

    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_setup(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_init(_)).WillOnce(Return(0));
    EXPECT_CALL(mock_file_system, ndef_restore_default_message(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_ndef_rwpayload_set(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_nfc_t4t_lib, nfc_t4t_emulation_start()).WillOnce(Return(0));

    EXPECT_EQ(0, nfc_t4t_init());
}

TEST_F(UtNfc, create_ndef_default_message_fails_when_k_mutex_lock_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(-1));

    EXPECT_NE(0, create_ndef_default_message(buffer, &buffer_size));
}

TEST_F(UtNfc, create_ndef_default_message_fails_when_nfc_ndef_uri_msg_encode_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_subsys_nfc, nfc_ndef_uri_msg_encode(_, _, _, _, _)).WillOnce(Return(1));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, create_ndef_default_message(buffer, &buffer_size));
}

TEST_F(UtNfc, create_ndef_default_message_fails_when_nfc_t4t_ndef_file_encode_fails)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    EXPECT_CALL(mock_zephyr_kernel, k_mutex_lock(_, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_subsys_nfc, nfc_ndef_uri_msg_encode(_, _, _, _, _)).WillOnce(Return(0));
    EXPECT_CALL(mock_subsys_nfc, nfc_t4t_ndef_file_encode(_, _)).WillOnce(Return(1));
    EXPECT_CALL(mock_zephyr_kernel, k_mutex_unlock(_)).Times(1);

    EXPECT_NE(0, create_ndef_default_message(buffer, &buffer_size));
}

TEST_F(UtNfc, create_ndef_default_message_success)
{
    uint32_t buffer_size = 10;
    uint8_t buffer[buffer_size] = {};

    InSequence s;

    nvs_ndef_default_message_success_expectations();

    EXPECT_EQ(0, create_ndef_default_message(buffer, &buffer_size));
}
