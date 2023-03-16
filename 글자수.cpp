#include <iostream>
#include <cstring>
using namespace std;

void f(char* k,int& p)
    {
        for(int i=0; k[i] !='\0'; i++){
            if(k[i] != '\0'){
                p++;
                continue;
            } else {
                break;

            }
        }}

int main(){
    char a[100] = "안녕하세요?";
    char b[100] = "날씨가 참 좋군요.";
    char c[100] = "안녕히 계세요!";


    cout << "함수사용" << endl;
    cout << strlen(a) << " " << strlen(b) << " " << strlen(c) << endl;

    int d, e, h;
        
    
    f(a, d);
    f(b, e);
    f(c, h);
    cout << "반복문으로 계산" << endl;
    cout << d << " " << e << " " << h << " " << endl;

    return 0;
}