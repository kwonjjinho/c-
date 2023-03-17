#include <stdio.h>

int main()
{
    int a, b;

    printf("두 각 입력: ");
    scanf("%d %d", &a, &b);

    printf("삼각형의 나머지 각 --> %d\n", 180 - a - b);

    return 0;
}