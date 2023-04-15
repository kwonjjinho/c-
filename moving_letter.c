#include <stdio.h>

int main() {
    char c;

    while (1) {
        printf("Press arrow key (or q to quit)\n");
        char input[3]; // 방향키 입력과 개행 문자, NULL 문자 총 3개
        fgets(input, sizeof(input), stdin); // 문자열 입력
        if (input[0] == 'q') { // 종료
            break;
        }

        // 문자열 끝에 있는 개행 문자 제거
        if (input[1] == '\n') {
            input[1] = '\0';
        }

        switch (input[0]) { // 첫번째 문자만 확인
            case 'A':
                printf("Up arrow key is pressed\n");
                break;
            case 'B':
                printf("Down arrow key is pressed\n");
                break;
            case 'C':
                printf("Right arrow key is pressed\n");
                break;
            case 'D':
                printf("Left arrow key is pressed\n");
                break;
            default:
                printf("Unknown key is pressed\n");
                break;
        }
    }

    return 0;
}