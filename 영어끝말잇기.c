#include <stdio.h>
#include <string.h>

int main() {
    char prev_word[100]; // 이전 단어를 저장하는 배열
    char curr_word[100]; // 현재 단어를 저장하는 배열
    int turn = 1; // 플레이어의 차례

    printf("끝말잇기 게임을 시작합니다!\n");
    printf("첫 번째 단어를 입력해주세요: ");
    scanf("%s", prev_word);

    while (1) { // 무한 루프
        printf("\n%d번 플레이어의 차례입니다.\n", turn);
        printf("이전 단어: %s\n", prev_word);
        printf("새로운 단어를 입력해주세요: ");
        scanf("%s", curr_word);

        // 이전 단어의 끝말과 현재 단어의 첫말이 일치하는지 확인
        if (prev_word[strlen(prev_word) - 1] == curr_word[0]) {
            printf("정답입니다! 다음 차례로 넘어갑니다.\n");
            strcpy(prev_word, curr_word); // 이전 단어를 현재 단어로 업데이트
            turn = (turn % 2) + 1; // 차례를 변경 (1 -> 2, 2 -> 1)
        }
        else {
            printf("오답입니다! 게임을 종료합니다.\n");
            break; // 루프를 종료
        }
    }return 0;
}
    