#include <stdio.h>

#define N 5   // 학습 데이터 개수

int main() {
  float x[N] = {1, 2, 3, 4, 5};   // 입력 데이터
  float y[N] = {2, 4, 6, 8, 10};  // 출력 데이터
  
  // 모델 파라미터 초기화
  float w = 0;
  float b = 0;
  
  // 학습
  float lr = 0.01;   // 학습률
  int epochs = 1000;  // 에포크 수
  for (int epoch = 0; epoch < epochs; epoch++) {
    float dw = 0;
    float db = 0;
    for (int i = 0; i < N; i++) {
      float y_pred = w * x[i] + b;   // 모델 예측값
      float error = y_pred - y[i];   // 오차 계산
      dw += error * x[i];   // 가중치 미분
      db += error;   // 절편 미분
    }
    w -= lr * dw / N;   // 가중치 업데이트
    b -= lr * db / N;   // 절편 업데이트
  }
  
  // 테스트
  float x_test = 6;   // 입력값
  float y_pred = w * x_test + b;   // 예측값
  
  // 출력
  printf("y_pred = %f\n", y_pred);
  
  return 0;
}