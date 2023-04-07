#include <stdio.h>

int main()
{
    int num1, num2, max;

    printf("두 수를 입력하시오:"); 
    scanf("%d %d",&num1,&num2);
    
    if (num1 > num2)
     max = num1;
    else 
     max = num2;
    printf("큰 수는 %d입니다.\n",max);

    if (num2 < 0 )
     printf("num2의 절대값은 %d\n",-num2);
    else
     printf("num2의 절대값은 %d\n",num2);
    
    printf("num1 = %d은",num1);
    if (num1 % 2 == 0)
     printf("짝수\n");
    else
     printf("홀수\n");
    
    return 0;
}