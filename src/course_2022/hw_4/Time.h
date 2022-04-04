#pragma once
#include <istream>

class Time {
private:
    int minutes;
    int hours;
    static int count;
public:
    Time(int h = 0, int m = 0);

    ~Time();

    void addMinutes(int m);

    void addHours(int h);

    Time operator+(Time &t) const;

    Time operator*(float k) const;

    static int getCount();

    friend std::ostream &operator<<(std::ostream &output, Time &time);
};