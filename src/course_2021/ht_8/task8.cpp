#include<iostream>
#include<stdio.h>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;

struct res {
    double x;
    double y;
    double ye;
};

const int N = 200001;
res arr[N];

//use your constant
//#define RAND_MAX 0x7fff

double gaussrand(double MO, double sko) {
    double sum = 0, x;
    for (int i = 0; i < 28; i++) {
        sum += 1.0 * rand() / RAND_MAX;
    }
    x = (sqrt(2.0) * (sko) * (sum - 14.)) / 2.11233 + MO;
    return x;
}

void writeRes(res *arr, int n, const char *output) {
    FILE *out = fopen(output, "w");
    if (!out) {
        printf("Error: cannot open the file\n");
        return;
    }
    fprintf(out, "%s", "X\tY\tY+e\n");
    int i;
    for (i = 0; i < n; ++i) {
        fprintf(out, "%4.8g\t%4.8g\t%4.8g\n", arr[i].x, arr[i].y, arr[i].ye);
        if (i % 10000 == 0){
            double progress = static_cast<double>(i+1)/n;
            cout << "[";
            int pos = 70 * progress;
            for (int i = 0; i < 70; ++i) {
                if (i < pos) cout << "=";
                else if (i == pos) cout << ">";
                else cout << " ";
            }
            cout << "] " << int(progress * 100.0) << " %\r";
            cout.flush();
        }
    }
    cout << "\nData has been written" << endl;
    fclose(out);
}

int main() {
    srand(time(0));
    const double sko = 15;
    for (int i = 0; i <= N; ++i) {
        arr[i].x = -10 + i * 0.0001;
        arr[i].y = 7 + arr[i].x * (3 - 4 * arr[i].x);
        arr[i].ye = gaussrand(arr[i].y, sko);
    }
    writeRes(arr, N, "D:\\univercpp\\src\\ht_8\\res.txt");
    return 0;
}
