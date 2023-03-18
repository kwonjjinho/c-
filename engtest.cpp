#include <iostream>
#include <cstring>
using namespace std;

int main() {
    string question[] = { "개", "고양이","기린","코끼리","표범"};
    string answer[] = { "dog","cat","giraffe","elephant","leopard"};
    string ox;   // 맞은때마다O, 틀릴때마다X 추가
    int score(0);

    cout<< "영단어로바꾸세요." << endl;
    for(int i=0; i<5; i++) {
        string youranswer;
        cout << question[i] << ':';
        cin >> youranswer;

        if (youranswer == answer[i]){
            ox += 'O';
            score += 20;
        }
        else {
             ox +='X';
        }
        }
     cout << "==> " << ox << " " << score << " 점입니다." << endl;
     return 0;
     } 