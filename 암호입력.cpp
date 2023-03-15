
#include <iostream>
using namespace std;

int main()
{
    string id("giicha2");
    int pw(1111);

    if(id == "giicha2"){
        if (pw == 1111){
            cout << "welcom" << endl;
        }
        else{
            cout << "not pw" << endl;
        }
    }
    else{
        cout << "who are you?" << endl;
    }

    return 0;
}