#include "mock_nvs.h"

int nvs_mount(struct nvs_fs *fs)
{
    return MockNvs::getInstance().nvs_mount(fs);
}

ssize_t nvs_write(struct nvs_fs *fs, uint16_t id, const void *data, size_t len)
{
    return MockNvs::getInstance().nvs_write(fs, id, data, len);
}

ssize_t nvs_read(struct nvs_fs *fs, uint16_t id, void *data, size_t len)
{
    return MockNvs::getInstance().nvs_read(fs, id, data, len);
}