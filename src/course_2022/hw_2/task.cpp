#include <iostream>
#include <vector>
#include "Complex.h"

using namespace std;

int main(){
    int n;
    cout << "Input amount of numbers:";
    cin >> n;
    vector<Complex> arr;
    for (int i = 0; i < n; ++i){
        Complex tmp;
        cout << "Re=";
        cin >> tmp.Re;
        cout << "Im=";
        cin >> tmp.Im;
        arr.push_back(tmp);
    }
    Complex sum = {0, 0};
    for (Complex i: arr){
        sum = add(sum, i);
    }
    cout << "Module of sum = " << modulo(sum) << endl;
    for (Complex i: arr){
        cout << modulo(i) << endl;
    }
    return 0;
}