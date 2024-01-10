#ifndef KERNEL_STRUCTS_H_
#define KERNEL_STRUCTS_H_

#include "sys/dlist.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        sys_dlist_t waitq;
    } _wait_q_t;

#ifdef __cplusplus
}
#endif

#endif