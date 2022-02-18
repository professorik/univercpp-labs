#include <iostream>
#include <string>

using namespace std;

void inputString(const string& fieldName, string &result){
    string tmp;
    cout << fieldName << ":";
    cin >> tmp;
    result.append(tmp).append(" ");
}

string inputData(){
    string res;
    inputString("Surname", res);
    inputString("Name", res);
    inputString("Patronymic", res);

    int age;
    cout << "Age:";
    cin >> age;
    res.append("\b, ").append(to_string(age));
    return res;
}

int main(){
    char tmp;
    do {
        cout << inputData() << endl;
        getchar();
        cout << "Do you want to continue? (y/n)\n";
        tmp = getchar();
        if (tmp != 'n' && tmp != 'y') cout << "Incorrect input\n";
    } while (tmp == 'y');
}