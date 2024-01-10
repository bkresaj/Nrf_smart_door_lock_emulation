#ifndef ORDINALS_H
#define ORDINALS_H

#include "../device_tree.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define DT_DEP_ORD(node_id) DT_CAT(node_id, _ORD)

#ifdef __cplusplus
}
#endif

#endif