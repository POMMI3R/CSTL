#include <stdio.h>
#include <utility/result.h>

#define CASE    break; case
#define DEFAULT break; default

RESULT_DEF(int, char*);

RESULT(int, char*) eval(int lhs, int rhs, char op) {
    switch (op) {
    CASE '+': return OK_NEW(int, char*, lhs + rhs);
    CASE '-': return OK_NEW(int, char*, lhs - rhs);
    CASE '*': return OK_NEW(int, char*, lhs * rhs);
    CASE '/': return rhs ? OK_NEW(int, char*, lhs / rhs) : ERR_NEW(int, char*, "Division by zero");
    DEFAULT : return ERR_NEW(int, char*, "Invalid operator");
    }
}

int main() {
    int lhs = 0, rhs = 0;
    char op = 0;

    scanf("%d %c %d", &lhs, &op, &rhs);

    RESULT(int, char*) result = eval(lhs, rhs, op);

    switch (result.tag) {
    CASE OK : printf("Ok! %d\n", result.ok);
    CASE ERR: printf("Error! %s\n", result.err);
    }

    return 0;
}
