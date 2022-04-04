#include <string>
#include <regex>
#include <iostream>

using namespace std;

class Train {
private:
    string name;
    int number;
    string timestamp;
public:
    Train() = default;

    int getNumber() const {
        return number;
    }

    bool after(string timestamp);

    friend ostream &operator<<(ostream &output, const Train &train) {
        output << train.name << " " << train.number << " " << train.timestamp;
        return output;
    }

    friend istream &operator>>(istream &input, Train &train) {
        getline(input >> ws, train.name);
        input >> train.number;
        getline(input >> ws, train.timestamp);
        if (!isTimeValid(train.timestamp)) {
            cout << "Invalid time format for string \"" << train.timestamp << "\"" << endl;
        }
        return input;
    }

    ~Train() = default;

    static bool isTimeValid(string timestamp) {
        // regex for 24-hour format string (dd:mm:yyyy hh:mm:ss)
        const regex pattern(
                "(0[1-9]|[1-2][0-9]|3[0-1])\\/(0[1-9]|1[0-2])\\/[0-9]{4} (2[0-3]|[0-1][0-9]):[0-5][0-9]:[0-5][0-9]");
        if (timestamp.empty())
            return false;
        return regex_match(timestamp, pattern);
    }
};

bool compareByNumber(Train &lhs, Train &rhs);
