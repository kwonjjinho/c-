#include <iostream>
#include <cstring>
using namespace std;

int main() {
    
    string un, pw1, pw2;

    cout << "이름 입력: " << endl;
    getline(cin, un);

    // 암호 입력 받기
    cout << "암호 입력: " << endl;
    getline(cin, pw1);

    // 암호 다시 입력 받기
    cout << "다시 입력: " << endl;
    getline(cin, pw2);

    // 입력한 두 암호가 같은지 확인하고 결과 출력하기
    if (pw1 == pw2) {
        cout << un <<"님께서 로그인 하셨습니다.";
    } else {
        cout << un <<"님 다시 입력하세요.";
    }

    return 0;
}