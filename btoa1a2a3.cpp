#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream fin("a1.txt");
    if (!fin) {cout << "읽기용 파일 열기오류"; return 0;}

    ifstream fin2("a2.txt");
    if (!fin2) {cout << "읽기용 파일 열기오류"; return 0;}

    ifstream fin3("a3.txt");
    if (!fin3) {cout << "읽기용 파일 열기오류"; return 0;}

    ofstream fout("b.txt", ios::app);
    if (!fout) {cout << "a1 파일 열기 오류"; return 0;}

    int c;
    while ((c = fin.get()) != EOF){
        fout << (char)c;
    }
    
    while ((c = fin2.get()) != EOF){
        fout << (char)c;
    }

    while ((c = fin3.get()) != EOF){
        fout << (char)c;
    }

    cout << "파일 추가쓰기 완료" << endl;

    fin.close();
    fin2.close();
    fin3.close();
    fout.close();
    

    return 0;
}