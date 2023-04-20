#include <iostream>
#include <string>
using namespace std;
int main() 
{
    string s;

    cout <<"문자열을 입력하세요" << endl;
    getline(cin,s);
    int len = s.length();

    for(int i=0; i<len; i++){
        if (s[0]<0){
        string first = s.substr(0,3);
        string sub = s.substr(3, len-3);
        s = sub + first;
        cout << s << endl;
        i+=2;}

        else{
            string first = s.substr(0,1);
            string sub = s.substr(1, len-1);
            s = sub + first;
            cout << s << endl;

        }

    }   
}