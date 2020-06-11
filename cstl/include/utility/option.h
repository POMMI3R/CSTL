
#ifndef OPTION_H
#define OPTION_H

#include <sys/types.h>
#include <stdarg.h>

#define NUMARGS(...) (sizeof((int[]){ __VA_ARGS__ }) / sizeof(int))

#define OPTION(T)                                       \
__STRUCT_OPTION_IMPL(T)                                 \
__FUNC_NONE_IMPL(T)                                     \
__FUNC_SOME_IMPL(T)                                     \
__FUNC_OPTION_IMPL(T)

#define Option(T) __STRUCT_OPTION_NAME(T)
#define __STRUCT_OPTION_NAME(T) __Option##T
#define __STRUCT_OPTION_IMPL(T)                         \
typedef struct {                                        \
    enum { NONE, SOME } tag;                            \
    T value;                                            \
} __STRUCT_OPTION_NAME(T);

#define none(T) __FUNC_NONE_NAME(T)()
#define __FUNC_NONE_NAME(T) __none_##T
#define __FUNC_NONE_IMPL(T)                             \
Option(T) __FUNC_NONE_NAME(T)(void) {                   \
    Option(T) ret = {                                   \
        .tag   = NONE,                                  \
        .value = 0                                      \
    }; return ret;                                      \
}

#define some(T, V) __FUNC_SOME_NAME(T)(V)
#define __FUNC_SOME_NAME(T) __some_##T
#define __FUNC_SOME_IMPL(T)                             \
Option(T) __FUNC_SOME_NAME(T)(T value) {                \
    Option(T) ret = {                                   \
        .tag   = SOME,                                  \
        .value = value                                  \
    }; return ret;                                      \
}

#define option(T, ...) __FUNC_OPTION_NAME(T)(NUMARGS(__VA_ARGS__), ##__VA_ARGS__)
#define __FUNC_OPTION_NAME(T) __option_##T
#define __FUNC_OPTION_IMPL(T)                           \
Option(T) __FUNC_OPTION_NAME(T)(ssize_t args, ...) {    \
    if (!args) return none(T);                          \
    va_list vl;                                         \
    va_start(vl, args);                                 \
    Option(T) ret = some(T, va_arg(vl, T));             \
    va_end(vl);                                         \
    return ret;                                         \
}

#endif
