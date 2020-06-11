
#include <stdio.h>
#include <utility/result.h>

#define CASE    break; case
#define DEFAULT break; default

// to avoid '*' in name of type
typedef char* String;

RESULT(int, String);

Result(int, String) eval(int lhs, int rhs, char op) {
    switch (op) {
    CASE '+': return ok(int, String, lhs + rhs);
    CASE '-': return ok(int, String, lhs - rhs);
    CASE '*': return ok(int, String, lhs * rhs);
    CASE '/': return rhs ? ok(int, String, lhs / rhs) : err(int, String, "Division by zero");
    DEFAULT : return err(int, String, "Invalid operator");
    }
}

int main() {
    int lhs = 0, rhs = 0;
    char op = 0;

    scanf("%d %c %d", &lhs, &op, &rhs);

    Result(int, String) answer = eval(lhs, rhs, op);

    switch (answer.tag) {
    CASE OK : printf("Ok! %d\n", answer.ok);
    CASE ERR: printf("Error! %s\n", answer.err);
    }

    return 0;
}
