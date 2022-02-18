#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void firstTask() {
    int n;
    cin >> n;
    int fib[2] = {0, 1};
    vector<float> res;
    cout << "1 ";
    for (int i = 2; i <= n; ++i) {
        int current = fib[0] + fib[1];
        res.push_back(static_cast<float>(current) / fib[1]);
        fib[0] = fib[1];
        fib[1] = current;
        cout << current << " ";
    }
    cout << endl;
    for (float i: res) {
        cout << i << " ";
    }
}

void secondTask() {
    float x;
    int n;
    cout << "Input n\n";
    cin >> n;
    do {
        cout << "Input x (0 < x < 10)\n";
        cin >> x;
    } while (abs(x - 5) >= 5);
    float sum = 1;
    float prev = 1;
    vector<float> res;
    for (int i = 1; i <= n; ++i) {
        prev *= x / i;
        sum += prev;
    }
    cout << sum << " " << exp(x);
}


void thirdTask() {
    int x;
    do {
        cout << "Enter your number [0-9]:\n";
        srand(time(0));
        cin >> x;
    } while (rand() % 10 != x);
    cout << "You won" << endl;
}

string getSeason(int month) {
    if (abs(month - 3) <= 1)
        return "Spring";
    else if (abs(month - 6) <= 1)
        return "Summer";
    else if (abs(month - 9) <= 1)
        return "Autumn";
    return "Winter";
}

void fourthTask() {
    time_t t = time(nullptr);
    tm *timePtr = localtime(&t);
    while (true) {
        cout << "1 - Say \"Hello!\" 20 times.\n"
             << "2 - 2 * 2 = ?\n"
             << "3 - What is the season now?\n"
             << "4 - Exit\n";
        int id;
        cin >> id;
        switch (id) {
            case 1:
                for (int i = 0; i < 20; ++i) cout << "Hello!\n";
                cout << flush;
                break;
            case 2:
                cout << "2 * 2 = " << 2 * 2 << endl;
                break;
            case 3:
                cout << getSeason(timePtr->tm_mon) << endl;
                break;
            case 4:
                return;
            default:
                cout << "Input num [1-4]" << endl;
        }
    }
}

int main() {
    //firstTask();
    //secondTask();
    //thirdTask();
    fourthTask();
    return 0;
}