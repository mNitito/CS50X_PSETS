#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x, y;

    int result;

    x = 3;
    y = 4;
    // using modulo operator
    result = x % y;
    printf("%d", result);

    result = y % x;
    printf("\n%d", result);

    // for different values
    x = 4;
    y = 2;
    result = x % y;
    printf("\n%d \n", result);

    return 0;
}