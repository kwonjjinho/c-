#include <stdio.h>

void swap(double *x, double*y){
    double temp;
    temp =*x;
    *x=*y;
    *y= temp;
}

int main(){
    double a,b;
    printf("두 실수 입력: ");
    scanf("%lf %lf",&a,&b);

    printf("before swap --> %lg %lg\n",a, b);
    swap(&a, &b);
    printf("after swap --> %lg %lg\n", a, b);

    return 0;
}