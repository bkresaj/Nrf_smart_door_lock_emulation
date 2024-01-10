#ifndef SYS_CLOCK_H_
#define SYS_CLOCK_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CONFIG_TIMEOUT_64BIT
    typedef int64_t k_ticks_t;
#else
typedef uint32_t k_ticks_t;
#endif

#define K_TICKS_FOREVER ((k_ticks_t)-1)

    typedef struct
    {
        k_ticks_t ticks;
    } k_timeout_t;

#ifdef __cplusplus
}
#endif

#endif