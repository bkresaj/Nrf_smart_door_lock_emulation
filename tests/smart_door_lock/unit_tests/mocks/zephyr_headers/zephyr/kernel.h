#ifndef KERNEL_H_
#define KERNEL_H_

#include <stdint.h>

#include "kernel_structs.h"
#include "sys/printk.h"
#include "sys_clock.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define K_MSEC(ms) ((k_timeout_t){.ticks = ms})

    struct k_mutex
    {
        /** Mutex wait queue */
        _wait_q_t wait_q;
        /** Mutex owner */
        struct k_thread *owner;

        /** Current lock count */
        uint32_t lock_count;

        /** Original thread priority */
        int owner_orig_prio;
    };

#define EPERM 1    /**< Not owner */
#define ENOENT 2   /**< No such file or directory */
#define ESRCH 3    /**< No such context */
#define EINTR 4    /**< Interrupted system call */
#define EIO 5      /**< I/O error */
#define ENXIO 6    /**< No such device or address */
#define E2BIG 7    /**< Arg list too long */
#define ENOEXEC 8  /**< Exec format error */
#define EBADF 9    /**< Bad file number */
#define ECHILD 10  /**< No children */
#define EAGAIN 11  /**< No more contexts */
#define ENOMEM 12  /**< Not enough core */
#define EACCES 13  /**< Permission denied */
#define EFAULT 14  /**< Bad address */
#define ENOTBLK 15 /**< Block device required */
#define EBUSY 16   /**< Mount device busy */
#define EEXIST 17  /**< File exists */
#define EXDEV 18   /**< Cross-device link */
#define ENODEV 19  /**< No such device */
#define ENOTDIR 20 /**< Not a directory */
#define EISDIR 21  /**< Is a directory */
#define EINVAL 22  /**< Invalid argument */
#define ENFILE 23  /**< File table overflow */
#define EMFILE 24  /**< Too many open files */
#define ENOTTY 25  /**< Not a typewriter */
#define ETXTBSY 26 /**< Text file busy */
#define EFBIG 27   /**< File too large */
#define ENOSPC 28  /**< No space left on device */
#define ESPIPE 29  /**< Illegal seek */
#define EROFS 30   /**< Read-only file system */
#define EMLINK 31  /**< Too many links */
#define EPIPE 32   /**< Broken pipe */

    int k_mutex_init(struct k_mutex *mutex);
    int k_mutex_lock(struct k_mutex *mutex, k_timeout_t timeout);
    int k_mutex_unlock(struct k_mutex *mutex);

#ifdef __cplusplus
}
#endif

#endif
