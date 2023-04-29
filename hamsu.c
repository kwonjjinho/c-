#include <stdio.h>

void area(int a,int b,int c){
    switch(c){
        case 1: 
          printf("원의 넓이는%g입니다.\n",a*a*3.141592);
        break;
        case 3:
         printf("삼각형의 넓이는%g입니다.\n",a*b /2.0);
        break;
        case 4:
         printf("사각형의 넓이는%d\n입니다.\n",a*b);
        break; 
        default:
         printf("그런 도형 아직 코딩 안되어 있습니다.");
        break; 

    }

}
int main(){
    int g, s, d;
    do{
        printf("가로세로 입력"); scanf("%d %d",&g, &s);
        if (g==0 || s==0) break;
        printf("몇각형>==>"); scanf("%d",&d);
        area(g,s,d);
    }while(1);

    printf("종료합니다.bye~\n");
    return 0;
}