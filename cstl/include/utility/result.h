
#ifndef RESULT_H
#define RESULT_H

#define RESULT_DEF(T, U)                            \
RESULT_IMPL(T, U)                                   \
OK_NEW_IMPL(T, U)                                   \
ERR_NEW_IMPL(T, U)

#define RESULT(T, U) RESULT_NAME(T, U)
#define RESULT_NAME(T, U) __Result##T
#define RESULT_IMPL(T, U)                           \
typedef struct {                                    \
    enum { OK, ERR } tag;                           \
    union {                                         \
        T ok;                                       \
        U err;                                      \
    };                                              \
} RESULT_NAME(T, U);

#define OK_NEW(T, U, V) OK_NEW_NAME(T, U)(V)
#define OK_NEW_NAME(T, U) __ok_##T
#define OK_NEW_IMPL(T, U)                           \
RESULT(T, U) OK_NEW_NAME(T, U)(T ok) {              \
    RESULT(T, U) ret = {                            \
        .tag = OK,                                  \
        .ok  = ok                                   \
    }; return ret;                                  \
}

#define ERR_NEW(T, U, V) ERR_NEW_NAME(T, U)(V)
#define ERR_NEW_NAME(T, U) __err_##T
#define ERR_NEW_IMPL(T, U)                          \
RESULT(T, U) ERR_NEW_NAME(T, U)(U err) {            \
    RESULT(T, U) ret = {                            \
        .tag = ERR,                                 \
        .err = err                                  \
    }; return ret;                                  \
}

#endif
