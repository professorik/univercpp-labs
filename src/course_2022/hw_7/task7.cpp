#include <iostream>
#include <cstdarg>

using namespace std;

int gcd(int a, int b){
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findGCD(int n, ...) {
    va_list nums;
    va_start(nums, n);
    int res = va_arg(nums, int);
    for(; n > 1; n--) {
        int i = va_arg(nums, int);
        if (i < 0)
            throw exception("Numbers can't be negative");
        else if (i == 0)
            throw exception("Numbers can't be zero");
        res = gcd(res, i);
    }
    va_end(nums);
    return res;
}

int main() {
    try {
        cout << findGCD(5, 12, 42, 3, 6, 2) << endl;
    } catch (exception& err) {
        cout << err.what() << endl;
    }
    try {
        cout << findGCD(5, 12, 42, 0, 6, 9) << endl;
    } catch (exception& err) {
        cout << err.what() << endl;
    }
    try {
        cout << findGCD(5, 12, 42, 3, -6, 9) << endl;
    } catch (exception& err) {
        cout << err.what() << endl;
    }
    return 0;
}