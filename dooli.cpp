#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
    ifstream fin("dooli.txt");
    ofstream fout("b.txt");
    if(!fin || !fout){
        cerr << "파일 열기 실패"; return 1;
    }
    string f,r;
    cout << "find: "; getline(cin, f);
    cout << "replace: "; getline(cin, r);
    
    string temp;
    while (getline(fin,temp)) {
        int findex = 0;
        int sindex = 0;
        while (true) {
            findex = temp.find(f,sindex);
            if (findex == -1) break;
            temp.replace(findex, f.length(), r);
            sindex = findex + r.length();  
        }
        fout << temp << endl;
    }
 
    return 0;
}