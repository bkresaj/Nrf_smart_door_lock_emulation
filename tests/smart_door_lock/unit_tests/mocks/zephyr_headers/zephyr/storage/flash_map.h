#ifndef FLASH_MAP_H_
#define FLASH_MAP_H_

#include "../device.h"

#ifdef __cplusplus
extern "C"
{
#endif

// real
// #define FIXED_PARTITION_DEVICE(label) \
//	DEVICE_DT_GET(DT_MTD_FROM_FIXED_PARTITION(DT_NODELABEL(label)))
// fake
#define FIXED_PARTITION_DEVICE(label) 1

// real
// #define FIXED_PARTITION_ID(label) DT_FIXED_PARTITION_ID(DT_NODELABEL(label))
// fake
#define FIXED_PARTITION_ID(label) 1

// real
// #define FIXED_PARTITION_OFFSET(label) DT_REG_ADDR(DT_NODELABEL(label))
// fake
#define storage_partition 1
#define FIXED_PARTITION_OFFSET(label) label

#ifdef __cplusplus
}
#endif

#endif