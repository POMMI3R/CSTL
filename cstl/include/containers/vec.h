
#ifndef VEC_H
#define VEC_H

#include <sys/types.h>
#include <stdlib.h>

#define __NPT(V) (1 << 32 - __builtin_clz(V - 1))

#define VEC(T)                                                  \
__STRUCT_VEC_IMPL(T)                                            \
__FUNC_VEC1_IMPL(T)                                             \
__FUNC_VEC2_IMPL(T)                                             \
__FUNC_VEC3_IMPL(T)

#define Vec(T) __STRUCT_VEC_NAME(T)
#define __STRUCT_VEC_NAME(T) __Vec##T
#define __STRUCT_VEC_IMPL(T)                                    \
typedef struct {                                                \
    ssize_t size, capacity;                                     \
    T* data;                                                    \
} __STRUCT_VEC_NAME(T);

#define vec1(T) __FUNC_VEC1_NAME(T)()
#define __FUNC_VEC1_NAME(T) __vec1_##T
#define __FUNC_VEC1_IMPL(T)                                     \
Vec(T) __FUNC_VEC1_NAME(T)(void) {                              \
    Vec(T) ret = {                                              \
        .size     = 0,                                          \
        .capacity = 1,                                          \
        .data     = malloc(sizeof(T))                           \
    }; return ret;                                              \
}

#define vec2(T, C) __FUNC_VEC2_NAME(T)(C)
#define __FUNC_VEC2_NAME(T) __vec2_##T
#define __FUNC_VEC2_IMPL(T)                                     \
Vec(T) __FUNC_VEC2_NAME(T)(ssize_t count) {                     \
    Vec(T) ret = {                                              \
        .size     = count,                                      \
        .capacity = __NPT(count),                               \
        .data     = malloc(__NPT(count) * sizeof(T))            \
    }; return ret;                                              \
}

#define vec3(T, C, V) __FUNC_VEC3_NAME(T)(C, V)
#define __FUNC_VEC3_NAME(T) __vec3_##T
#define __FUNC_VEC3_IMPL(T)                                     \
Vec(T) __FUNC_VEC3_NAME(T)(ssize_t count, T value) {            \
    Vec(T) ret = {                                              \
        .size     = count,                                      \
        .capacity = __NPT(count),                               \
        .data     = malloc(__NPT(count) * sizeof(T))            \
    };                                                          \
                                                                \
    for (T* iter = ret.data; iter != ret.data + count; ++iter)  \
        *iter = value;                                          \
                                                                \
    return ret;                                                 \
}

#endif
