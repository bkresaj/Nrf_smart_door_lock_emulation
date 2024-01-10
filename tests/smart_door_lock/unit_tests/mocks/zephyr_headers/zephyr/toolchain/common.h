#ifndef COMMON_H_
#define COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define _DO_CONCAT(x, y) x##y
#define _CONCAT(x, y) _DO_CONCAT(x, y)

#ifdef __cplusplus
}
#endif

#endif