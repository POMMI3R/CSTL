
#ifndef RESULT_H
#define RESULT_H

#define RESULT(T, U)                                    \
__STRUCT_RESULT_IMPL(T, U)                              \
__FUNC_OK_IMPL(T, U)                                    \
__FUNC_ERR_IMPL(T, U)

#define Result(T, U) __STRUCT_RESULT_NAME(T, U)
#define __STRUCT_RESULT_NAME(T, U) __Result##T##U
#define __STRUCT_RESULT_IMPL(T, U)                      \
typedef struct {                                        \
    enum { OK, ERR } tag;                               \
    union {                                             \
        T ok;                                           \
        U err;                                          \
    };                                                  \
} __STRUCT_RESULT_NAME(T, U);

#define ok(T, U, V) __FUNC_OK_NAME(T, U)(V)
#define __FUNC_OK_NAME(T, U) __ok_##T##U
#define __FUNC_OK_IMPL(T, U)                            \
Result(T, U) __FUNC_OK_NAME(T, U)(T ok) {               \
    Result(T, U) ret = {                                \
        .tag = OK,                                      \
        .ok  = ok                                       \
    }; return ret;                                      \
}

#define err(T, U, V) __FUNC_ERR_NAME(T, U)(V)
#define __FUNC_ERR_NAME(T, U) __err_##T##U
#define __FUNC_ERR_IMPL(T, U)                           \
Result(T, U) __FUNC_ERR_NAME(T, U)(U err) {             \
    Result(T, U) ret = {                                \
        .tag = ERR,                                     \
        .err = err                                      \
    }; return ret;                                      \
}

#endif
