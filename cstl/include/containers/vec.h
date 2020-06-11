
#ifndef VEC_H
#define VEC_H

#include <sys/types.h>
#include <stdlib.h>

#define VEC(T)                                          \
__STRUCT_VEC_IMPL(T)

#define Vec(T) __STRUCT_VEC_NAME(T)
#define __STRUCT_VEC_NAME(T) __Vec##T
#define __STRUCT_VEC_IMPL(T)                            \
typedef struct {                                        \
    ssize_t size, capacity;                            \
    T* data;                                            \
} __STRUCT_VEC_NAME(T);

#endif
