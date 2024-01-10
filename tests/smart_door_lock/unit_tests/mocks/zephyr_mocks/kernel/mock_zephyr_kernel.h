#pragma once

#include <gmock/gmock.h>
#include <singleton_template.h>
#include <zephyr/kernel.h>

class MockZephyrKernel : public SingletonTemplate<MockZephyrKernel>
{
   public:
    MOCK_METHOD(int, k_mutex_init, (struct k_mutex * mutex), ());
    MOCK_METHOD(int, k_mutex_lock, (struct k_mutex * mutex, k_timeout_t timeout), ());
    MOCK_METHOD(int, k_mutex_unlock, (struct k_mutex * mutex), ());
};