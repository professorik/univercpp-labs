#include "Time.h"
#include <iostream>

int Time::count = 0;

void correctTime(int& hours, int& minutes);

Time::Time(int h, int m) {
    ++count;
    hours = h;
    minutes = m;
    correctTime(hours, minutes);
    std::cout << "Created. Total amount: " << count << std::endl;
}

Time::~Time() {
    --count;
    std::cout << "Deleted. Total amount: " << count << std::endl;
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
    return Time(0, k*(minutes + hours * 60));
}

Time Time::operator+(Time &t) const {
    return Time(t.hours + this->hours, t.minutes + this->minutes);
}

std::ostream &operator<<(std::ostream &output, Time &time) {
    output << time.hours << ":" << time.minutes;
    return output;
}

void correctTime(int& hours, int& minutes){
    hours += minutes/60;
    minutes %= 60;
}