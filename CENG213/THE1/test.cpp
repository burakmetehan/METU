#include <iostream>

using namespace std;

int main(){
    int *temp1 = new int;
    int *temp2=NULL, *temp3=NULL;

    cout << "temp1: " << temp1 << " temp2: " << temp2 <<  "temp3: " << temp3 << endl;

    temp2 = temp3 = temp1;

    cout << "temp1: " << temp1 << " temp2: " << temp2 <<  " temp3: " << temp3 << endl;

    return 0;
}