#ifndef PRINTK_H_
#define PRINTK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

#define printk(format, ...) 0 && printf(format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
