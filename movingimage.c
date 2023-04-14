#include <stdio.h>
#include <stdlib.h>

int main() { 
    int k, sp;
    for (k = 0; k < 80; k++){/* 50번 UFO 출력 */
        system("clear"); 
        if (k%2 ==0)
            printf("\n");
        for (sp = 0; sp < k; sp++)
            printf(" "); /* 점점 공백 많아짐 */
        printf("<#=#>\n"); 
        system("sleep 0.04");
    }

}
