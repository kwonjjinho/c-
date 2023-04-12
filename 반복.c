#include <stdio.h>
# include <stdlib.h>
#include <string.h>
int main(){
    int or;
    char* so;
    for(or = 10; or > 0; or-=1){
        if (or % 2 == 0)
         so = "^ ~ ^";
        else 
         so = "- _ -";
        system("clear");
        printf("%d마리 통닭 튀긴다.%s\n",or, so);
        system("sleep 1");
    }
    printf("다튀겼다!");
    return 0;
}