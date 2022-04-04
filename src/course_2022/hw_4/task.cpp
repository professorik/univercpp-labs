#include <iostream>
#include "Time.h"

using namespace std;

int main(){
    Time a;
    Time b = Time(1, 3);
    a.addHours(2);
    a.addMinutes(61);
    Time c = a + b;
    Time d = a * 5;
    {
        Time temp;
    }
    cout << c << "\n" << d << "\n";
    a = c;
    d = a * 5 * 5;
    cout << c << "\n" << d << "\n";
    Time superTotal = a + b + c + d;
    cout << superTotal << "\n";
    return 0;
}