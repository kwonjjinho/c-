#include <stdio.h>

int main()
{
    long long num;
    printf("원하는 한달 용돈 액수: ");
    scanf("%lld",&num);
    printf("==> 3개월치 용돈 %lld 원이 한번에 입금되었습니다.\n", num * 3);
    
    return 0;
}