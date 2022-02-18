#include <iostream>
#include <thread>

using namespace std;

void foo(int Z)
{
    for (int i = 0; i < Z; i++) {
        cout << "Thread using function"
                " pointer as callable\n";
    }
}

int main()
{
    thread th1(foo, 3);
    th1.join();
    return 0;
}