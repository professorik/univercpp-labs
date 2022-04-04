#include "Train.h"
#include <sstream>

bool compareByNumber(Train &lhs, Train &rhs) {
    return lhs.getNumber() > rhs.getNumber();
}

bool Train::after(string timestamp) {
    stringstream first(timestamp);
    stringstream second(this->timestamp);
    string date1, time1, date2, time2;
    first >> date1 >> time1;
    second >> date2 >> time2;
    return date1 == date2 && time1 < time2;
}