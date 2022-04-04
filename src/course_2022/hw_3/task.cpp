#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include "Train.h"

using namespace std;

// Variant 3
int main() {
    vector<Train> station;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (!(fin && fout))
        return 1;

    string date;
    int N;
    fin >> date >> N;
    for (int i = 0; i < N; ++i) {
        Train tmp;
        fin >> tmp;
        station.push_back(tmp);
    }

    sort(station.begin(), station.end(), compareByNumber);

    for (Train &train: station) {
        if (train.after(date.append(" 15:00:00")))
            fout << train << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}