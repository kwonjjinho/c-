#include <stdio.h>

int main()
{
    char a;
    printf("영문자하나 입력");
    scanf("%c",&a);

    if(a >= 'A' && a <= 'Z' )
        printf("Large\n");
    else if(a <= 'z' && a >= 'a')
        printf("Small\n");
    else
        printf("기타\n");
    
    return 0;

}