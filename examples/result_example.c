
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

RESULT(int, Error);

Result(int, Error) eval(int lhs, int rhs, char op) {
    switch (op) {
    CASE '+': return ok(int, Error, lhs + rhs);
    CASE '-': return ok(int, Error, lhs - rhs);
    CASE '*': return ok(int, Error, lhs * rhs);
    CASE '/': return rhs ? ok(int, Error, lhs / rhs) : err(int, Error, DIVISION_BY_ZERO);
    DEFAULT : return err(int, Error, INVALID_OPERATOR);
    }
}

int main() {
    int lhs = 0, rhs = 0;
    char op = 0;

    scanf("%d %c %d", &lhs, &op, &rhs);

    Result(int, Error) answer = eval(lhs, rhs, op);

    switch (answer.tag) {
    CASE OK : printf("Ok! %d\n", answer.ok);
    CASE ERR: printf("Error! %s\n", error_message[ answer.err ]);
    }

    return 0;
}
