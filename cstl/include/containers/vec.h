
#ifndef VEC_H
#define VEC_H

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <utility/option.h>

#define __NPT(V) (1 << 32 - __builtin_clz((V) - 1))

#define VEC(T)                                                  \
__STRUCT_VEC_IMPL(T)                                            \
__FUNC_VEC1_IMPL(T)                                             \
__FUNC_VEC2_IMPL(T)                                             \
__FUNC_VEC3_IMPL(T)                                             \
__FUNC_VEC4_IMPL(T)

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

#define vec4(T, S) __FUNC_VEC4_NAME(T)(S)
#define __FUNC_VEC4_NAME(T) __vec4_##T
#define __FUNC_VEC4_IMPL(T)                                     \
Vec(T) __FUNC_VEC4_NAME(T)(Vec(T) self) {                       \
    T* new_data = malloc(self.size * sizeof(T));                \
    memcpy(new_data, self.data, self.size * sizeof(T));         \
    self.data = new_data;                                       \
    return self;                                                \
}

#define vec_at(T, S, I) ((S).data[ (I) ])

#define vec_at_safe(T, S, I) ((I) < (S).size ? option((T), (S).data[ (I) ]) : option(T))

#define vec_back(T, S) ((S).data[ (S).size - 1 ])

#define vec_back_safe(T, S) ((S).size >= 0 ? option(T, (S).data[ (S).size - 1 ]) : option(T))

#define vec_begin(T, S) ((S).data)

#define vec_end(T, S) ((S).data + (S).size)

#define vec_empty(T, S) ((S).size == 0)

#define vec_reserve_apply(T, S, V) {                            \
    T* new_data = malloc((V) * sizeof(T));                      \
    memcpy(new_data, (S).data, (S).size * sizeof(T));           \
    (S).data = new_data;                                        \
}

#define vec_shrink_apply(T, S) (vec_reserve((T), (S), (S).size))

#define vec_resize_apply(T, S, V) ((V) <= (S).capacity ? ((S).size = (V)) : (vec_reserve_apply((T), (S), (V)), (S).size = (V)))

#define vec_clear_apply(T, S) ((S).size = 0)

#define vec_insert_apply(T, S, I, V) {                          \
    if ((S).size == (S).capacity)                               \
        vec_reserve((S).capacity * 2)                           \
                                                                \
    for (int i = (S).size++; i > (I); --i)                      \
        (S).data[ i ] = (S).data[ i - 1 ];                      \
    (S).data[ i ] = (V);                                        \
}

#define vec_insert_apply_safe(T, S, I, V) ((0 <= (I) && (I) <= (S).size) ? (vec_insert_apply(T, S, I, V), true) : false)

#define vec_erase_apply(T, S, I) {                              \
    for (int i = (I); i < (S).size - 1; --i)                    \
        (S).data[ i ] = (S).data[ i + 1 ];                      \
    --(S).size;                                                 \
}

#define vec_erase_apply_safe(T, S, I) ((0 <= (I) && (I) < (S).size) ? (vec_erase_apply(T, S, I), true) : false)

#define vec_push_back_apply(T, S, V) {                          \
    if ((S).size == (S).capacity)                               \
        vec_reserve((S).capacity * 2)                           \
                                                                \
    (S).data[ (S).size++ ] = (V);                               \
}

#define vec_pop_back_apply(T, S) (--(S).size)

#define vec_pop_back_apply_safe(T, S) ((S).size > 0 ? (--(S).size, true): false)

#define vec_destructor(T, S) (free((S).data))

#endif
