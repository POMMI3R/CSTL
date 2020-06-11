
#ifndef OPTION_H
#define OPTION_H

#include <sys/types.h>
#include <stdarg.h>

#define NUMARGS(...) (sizeof((int[]){ __VA_ARGS__ }) / sizeof(int))

#define OPTION_DEF(T)                               \
OPTION_IMPL(T)                                      \
NONE_NEW_IMPL(T)                                    \
SOME_NEW_IMPL(T)                                    \
OPTION_NEW_IMPL(T)

#define OPTION(T) OPTION_NAME(T)
#define OPTION_NAME(T) Option_##T
#define OPTION_IMPL(T)                              \
typedef struct {                                    \
    enum { NONE, SOME } tag;                        \
    T value;                                        \
} OPTION_NAME(T);

#define NONE_NEW(T)
#define NONE_NEW_NAME(T) none_##T
#define NONE_NEW_IMPL(T)                            \
OPTION(T) NONE_NEW_NAME(T)(void) {                  \
    OPTION(T) ret = {                               \
        .tag   = NONE                               \
        .value = 0;                                 \
    }; return ret;                                  \
}

#define SOME_NEW(T, V) SOME_NEW_NAME(T)(V)
#define SOME_NEW_NAME(T) some_##T
#define SOME_NEW_IMPL(T)                            \
OPTION(T) SOME_NEW_NAME(T)(T value) {               \
    OPTION(T) ret = {                               \
        .tag   = SOME,                              \
        .value = value                              \
    }; return ret;                                  \
}

#define OPTION_NEW(T, ...) OPTION_NEW_NAME(T)(NUMARGS(__VA_ARGS__), ##__VA_ARGS__)
#define OPTION_NEW_NAME(T) option_##T
#define OPTION_NEW_IMPL(T)                          \
OPTION(T) OPTION_NEW_NAME(T)(ssize_t args, ...) {   \
    if (!args)                                      \
        return NONE_NEW(T);                         \
    va_list vl;                                     \
    va_start(vl, args);                             \
    OPTION(T) ret = SOME_NEW(T, va_arg(vl, T));     \
    va_end(vl);                                     \
    return ret;                                     \
}

#endif
