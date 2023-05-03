#include <stdio.h>

long long factorial(int n){
    long long fac = 1;
    while(n>0){
        fac *= n;
        n--;
    }
    return fac;
}

int main(){
    int n;
    printf("몇 팩토리얼? ==>");
    scanf("%d", &n);

    printf("%lld 입니다.\n",factorial(n));

    return 0;
}
