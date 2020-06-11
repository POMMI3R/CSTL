
#include <stdio.h>
#include <utility/result.h>

#define CASE    break; case
#define DEFAULT break; default

typedef enum {
    DIVISION_BY_ZERO,
    INVALID_OPERATOR
} Error;

char* error_message[] = {
    "Division by zero",
    "Invalid operator"
};

RESULT_DEF(int, Error);

RESULT(int, Error) eval(int lhs, int rhs, char op) {
    switch (op) {
    CASE '+': return OK_NEW(int, Error, lhs + rhs);
    CASE '-': return OK_NEW(int, Error, lhs - rhs);
    CASE '*': return OK_NEW(int, Error, lhs * rhs);
    CASE '/': return rhs ? OK_NEW(int, Error, lhs / rhs) : ERR_NEW(int, Error, DIVISION_BY_ZERO);
    DEFAULT : return ERR_NEW(int, Error, INVALID_OPERATOR);
    }
}

int main() {
    int lhs = 0, rhs = 0;
    char op = 0;

    scanf("%d %c %d", &lhs, &op, &rhs);

    RESULT(int, Error) result = eval(lhs, rhs, op);

    switch (result.tag) {
    CASE OK : printf("Ok! %d\n", result.ok);
    CASE ERR: printf("Error! %s\n", error_message[ result.err ]);
    }

    return 0;
}
