#include "mock_zephyr_kernel.h"

int k_mutex_init(struct k_mutex *mutex)
{
    return MockZephyrKernel::getInstance().k_mutex_init(mutex);
}

int k_mutex_lock(struct k_mutex *mutex, k_timeout_t timeout)
{
    return MockZephyrKernel::getInstance().k_mutex_lock(mutex, timeout);
}

int k_mutex_unlock(struct k_mutex *mutex)
{
    return MockZephyrKernel::getInstance().k_mutex_unlock(mutex);
}