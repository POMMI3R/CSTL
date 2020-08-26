
#include <stdio.h>
#include <utility/option.h>

#define CASE    break; case
#define DEFAULT break; default

OPTION(int);

Option(int) try_division(int lhs, int rhs) {
    // return rhs ? some(int, lhs / rhs) : none(int);
    return rhs ? option(int, lhs / rhs) : option(int);
}

int main() {
    int lhs = 0, rhs = 0;

    scanf("%d %d", &lhs, &rhs);

    Option(int) division = try_division(lhs, rhs);

    switch (division.tag) {
    CASE SOME: printf("Ok! %d\n", division.value);
    CASE NONE: printf("Error!\n");
    }

    return 0;
}
