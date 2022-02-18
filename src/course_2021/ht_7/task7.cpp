#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<cmath>

#define _stars_num 120000
#define w 20
#define _p_num 6
using namespace std;

string params[_p_num] = {"RA", "DEC", "PLX", "MURA", "MUDEC", "HPMAG"};

int n;
double Stars[_stars_num][_p_num];

void skipLine(FILE *f) {
    while (!feof(f)) {
        if (fgetc(f) == '\n') { break; }
    }
}

void readData(const char *input) {
    FILE *f = fopen(input, "r");
    if (!f) {
        cout << "Error: cannot open the file" << endl;
        return;
    }
    n = 0;
    while (!feof(f)) {
        int temp = 0;
        for (int i = 0; i < _p_num; ++i) {
            temp += fscanf(f, "%lf", &Stars[n][i]);
        }
        if (temp == _p_num) {
            if (++n % 10000 == 0)
                cout << "loaded " << n << " stars" << endl;
        } else { skipLine(f); }
    }
    cout << "loaded " << n << " objects" << endl;
    fclose(f);
}


int main() {
    readData("HIP2.txt");
    cout << setw(w) << "Param" << setw(w) << "Arithmetic Mean" << setw(w) << "Dispercy" << setw(w) << "Asymmetry" << setw(w) << "Excess\n";
    for (int j = 0; j < _p_num; ++j) {
        double arMean, asymmetry, excess, dis, u3, u4;
        u3 = u4 = arMean = dis = 0;
        for (int i = 0; i < n; ++i) {
            arMean += (Stars[i][j] - arMean) / double(i + 1);
        }
        for (int i = 0; i < n; ++i) {
            dis += (pow(Stars[i][j] - arMean, 2) - dis) / double(i + 1);
            u3 += (pow(Stars[i][j] - arMean, 3) - u3) / double(i + 1);
            u4 += (pow(Stars[i][j] - arMean, 4) - u4) / double(i + 1);
        }
        asymmetry = u3 / pow(dis, 1.5);
        excess = (u4 / (dis * dis)) - 3;
        cout << setw(w)<< params[j] << setw(w) << arMean << setw(w) << dis << setw(w) << asymmetry << setw(w) << excess << "\n";
    }
    return 0;
}
