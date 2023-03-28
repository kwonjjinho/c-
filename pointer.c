#include <stdio.h>

int main() {
  char str_arr[3][10] = {"hello", "world", "c"}; // 문자열 배열 선언 및 초기화

  // 문자열 배열을 사용하여 모든 문자열 출력
  printf("String array elements using array notation: \n");
  for (int i = 0; i < 3; i++) {
    printf("%s ", str_arr[i]);
  }
  printf("\n");

  // 포인터를 사용하여 문자열 출력
  printf("String array elements using pointer notation: \n");
  char *ptr_arr[3];
  for (int i = 0; i < 3; i++) {
    ptr_arr[i] = str_arr[i];
  }
  for (int i = 0; i < 3; i++) {
    printf("%s ", *(ptr_arr + i));
  }
  printf("\n");

  return 0;
}