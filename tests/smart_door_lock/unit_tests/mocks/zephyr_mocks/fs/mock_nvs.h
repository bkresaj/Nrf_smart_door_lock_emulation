#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>
#include <zephyr/types.h>

class MockNvs : public SingletonTemplate<MockNvs>
{
   public:
    MOCK_METHOD(int, nvs_mount, (struct nvs_fs * fs), ());
    MOCK_METHOD(ssize_t, nvs_write, (struct nvs_fs * fs, uint16_t id, const void *data, size_t len), ());
    MOCK_METHOD(ssize_t, nvs_read, (struct nvs_fs * fs, uint16_t id, void *data, size_t len), ());
};