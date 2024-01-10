#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdbool.h>

#include "device_tree.h"
#include "device_tree/ordinals.h"
#include "toolchain/common.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct device_state
    {
        /**
         * Device initialization return code (positive errno value).
         *
         * Device initialization functions return a negative errno code if they
         * fail. In Zephyr, errno values do not exceed 255, so we can store the
         * positive result value in a uint8_t type.
         */
        uint8_t init_res;

        /** Indicates the device initialization function has been
         * invoked.
         */
        bool initialized : 1;
    };

    struct device
    {
        /** Name of the device instance */
        const char *name;
        /** Address of device instance config information */
        const void *config;
        /** Address of the API structure exposed by the device instance */
        const void *api;
        /** Address of the common device state */
        struct device_state *state;
        /** Address of the device instance private data */
        void *data;
#if defined(CONFIG_DEVICE_DEPS) || defined(__DOXYGEN__)
        /**
         * Optional pointer to dependencies associated with the device.
         *
         * This encodes a sequence of sets of device handles that have some
         * relationship to this node. The individual sets are extracted with
         * dedicated API, such as device_required_handles_get(). Only available
         * if @kconfig{CONFIG_DEVICE_DEPS} is enabled.
         */
        Z_DEVICE_DEPS_CONST device_handle_t *deps;
#endif /* CONFIG_DEVICE_DEPS */
#if defined(CONFIG_PM_DEVICE) || defined(__DOXYGEN__)
        /**
         * Reference to the device PM resources (only available if
         * @kconfig{CONFIG_PM_DEVICE} is enabled).
         */
        struct pm_device *pm;
#endif
    };

#define DEVICE_NAME_GET(dev_id) _CONCAT(__device_, dev_id)
#define Z_DEVICE_DT_DEV_ID(node_id) _CONCAT(dts_ord_, DT_DEP_ORD(node_id))
#define DEVICE_DT_NAME_GET(node_id) DEVICE_NAME_GET(Z_DEVICE_DT_DEV_ID(node_id))
#define DEVICE_DT_GET(node_id) (DEVICE_DT_NAME_GET(node_id))

#ifdef __cplusplus
}
#endif

#endif
