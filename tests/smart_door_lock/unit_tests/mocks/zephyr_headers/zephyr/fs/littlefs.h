#ifndef LITTLEFS_H_
#define LITTLEFS_H_

#include "../storage/flash_map.h"
#include "fs_interface.h"

#ifdef __cplusplus
extern "C"
{
#endif

// real
/*#define FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(name)			 \
        FS_LITTLEFS_DECLARE_CUSTOM_CONFIG(name,				 \
                                          CONFIG_FS_LITTLEFS_READ_SIZE,	 \
                                          CONFIG_FS_LITTLEFS_PROG_SIZE,	 \
                                          CONFIG_FS_LITTLEFS_CACHE_SIZE, \
                                          CONFIG_FS_LITTLEFS_LOOKAHEAD_SIZE)*/

// fake
#define FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(name) name

#ifdef __cplusplus
}
#endif

#endif