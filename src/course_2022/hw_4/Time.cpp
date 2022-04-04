#include "Time.h"
#include <iostream>

int Time::count = 0;

void correctTime(int& hours, int& minutes);

Time::Time(int h, int m) {
    ++count;
    hours = h;
    minutes = m;
    correctTime(hours, minutes);
    std::cout << "Created new Time instance. Total amount: " << count << std::endl;
}

Time::~Time() {
    --count;
    std::cout << "Deleted new Time instance. Total amount: " << count << std::endl;
}

void Time::addMinutes(int m) {
    minutes += m;
    correctTime(hours, minutes);
}

void Time::addHours(int h) {
    hours += h;
}

int Time::getCount() {
    return count;
}

Time Time::operator*(float k) const {
    int _minutes = k * this->minutes;
    int _hours = k * this->hours;
    correctTime(_hours, _minutes);
    return Time(_hours, _minutes);
}

Time Time::operator+(Time &t) const {
    int _minutes = t.minutes + this->minutes;
    int _hours = t.hours + this->hours;
    correctTime(_hours, _minutes);
    return Time(_hours, _minutes);
}

std::ostream &operator<<(std::ostream &output, Time &time) {
    output << time.hours << ":" << time.minutes;
    return output;
}

void correctTime(int& hours, int& minutes){
    hours += minutes/60;
    minutes %= 60;
}