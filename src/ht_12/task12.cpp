#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;

struct frame {
    double t;
    double x;
    double y;
    double vx;
    double vy;
    double v;
};

void writeData(const char *output, vector<frame> &frames) {
    FILE *f = fopen(output, "w");
    if (!f) {
        cout << "Error: cannot open the file" << endl;
        return;
    }
    cout << "Writing data..." << endl;
    for (int i = 0; i < frames.size(); ++i) {
        fprintf(f, "%lf\t%4.3g\t%4.3g\t%4.3g\t%4.3g\t%4.3g\n", frames[i].t, frames[i].x, frames[i].y, frames[i].vx,
                frames[i].vy, frames[i].v);
    }
    cout << "loaded " << frames.size() << " objects" << endl;
    fclose(f);
}

const double C = 0.15, g = 9.8, air_den = 1.29, pi = acos(-1);
double _v0 = 1000, _h0 = 0, alpha = 45, ro = 7900, R = 0.05, b, m;

double fvx(double vy, double vx) {
    return -b * vx * sqrt(vx * vx + vy * vy) / m;
}

double fvy(double vy, double vx) {
    return -g - b * vy * sqrt(vx * vx + vy * vy) / m;
}

void euler(double delta, vector<frame> &ans) {
    ans.clear();
    double t = 0, x = 0, y = _h0, v = _v0;
    double vx = v * cos(alpha), vy = v * sin(alpha);
    do {
        x += vx * delta + fvx(vy, vx) * delta * delta / 2;
        y += vy * delta + fvy(vy, vx) * delta * delta / 2;
        vx += fvx(vy, vx) * delta;
        vy += fvy(vy, vx) * delta;
        v = sqrt(vx * vx + vy * vy);
        t += delta;
        if (abs(x) < 1e-9) x = 0;
        if (abs(y) < 1e-9) y = 0;
        ans.push_back({t, x, y, vx, vy, v});
    } while (y > 0);
}

void rk(double delta, vector<frame> &ans) {
    ans.clear();
    double t = 0, x = 0, y = _h0, v = _v0;
    double vx = v * cos(alpha), vy = v * sin(alpha);
    do {
        x += vx * delta + fvx(vy, vx) * delta * delta / 2;
        y += vy * delta + fvy(vy, vx) * delta * delta / 2;
        double k1 = fvx(vy, vx);
        double k2 = fvx(vy + delta / 2, vx + k1 * delta / 2);
        double k3 = fvx(vy + delta / 2, vx + k2 * delta / 2);
        double k4 = fvx(vy + delta, vx + k3 * delta);
        vx += delta * (k1 + 2*k2 + 2*k3 + k4) / 6;
        k1 = fvy(vy, vx);
        k2 = fvy(vy + k1 * delta / 2, vx + delta / 2);
        k3 = fvy(vy + k2 * delta / 2, vx + delta / 2);
        k4 = fvy(vy + k3 * delta, vx + delta);
        vy += delta * (k1 + 2*k2 + 2*k3 + k4) / 6;
        v = sqrt(vx * vx + vy * vy);
        t += delta;
        if (abs(x) < 1e-9) x = 0;
        if (abs(y) < 1e-9) y = 0;
        ans.push_back({t, x, y, vx, vy, v});
    } while (y > 0);
}

int main(int argc, char **argv) {
    if (argc == 6) {
        _v0 = atof(argv[1]);
        _h0 = atof(argv[2]);
        alpha = atof(argv[3]);
        ro = atof(argv[4]);
        R = atof(argv[5]);
    } else cerr << "Warning! Incorrect input format: 5 params are required" << endl;
    alpha *= pi / 180.0;
    b = 0.5 * C * air_den * pi * R * R;
    m = ro * 4 * pi * R * R * R / 3.0;
    vector<frame> ans;
    euler(1, ans);
    writeData("D:/univercpp/src/ht_12/euler1.txt", ans);
    euler(0.1, ans);
    writeData("D:/univercpp/src/ht_12/euler01.txt", ans);
    rk(1, ans);
    writeData("D:/univercpp/src/ht_12/rk1.txt", ans);
    rk(0.1, ans);
    writeData("D:/univercpp/src/ht_12/rk01.txt", ans);
}
