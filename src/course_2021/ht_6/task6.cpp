#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct dot2d {
    double x;
    double y;
};

bool comp(dot2d a, dot2d b) {
    return a.x < b.x;
}

struct dot3d {
    double x;
    double y;
    double z;
};

class cubic_spline {
private:
    struct spline_tuple {
        double a, b, c, d, x;
    };
    spline_tuple *splines;
    int n;

    void free_mem() {
        delete[] splines;
        splines = NULL;
    }

public:
    cubic_spline() : splines(NULL) {
    }

    void build_spline(dot2d *data, int n) {
        sort(data, data + n, comp);
        free_mem();
        this->n = n;
        splines = new spline_tuple[n];
        for (int i = 0; i < n; ++i) {
            splines[i].x = data[i].x;
            splines[i].a = data[i].y;
        }
        splines[0].c = 0.;
        double *alpha = new double[n - 1];
        double *beta = new double[n - 1];
        double A, B, C, F, h_i, h_i1, z;
        alpha[0] = beta[0] = 0.;
        for (int i = 1; i < n - 1; ++i) {
            h_i = data[i].x - data[i - 1].x, h_i1 = data[i + 1].x - data[i].x;
            A = h_i;
            C = 2. * (h_i + h_i1);
            B = h_i1;
            F = 6. * ((data[i + 1].y - data[i].y) / h_i1 - (data[i].y - data[i - 1].y) / h_i);
            z = (A * alpha[i - 1] + C);
            alpha[i] = -B / z;
            beta[i] = (F - A * beta[i - 1]) / z;
        }

        splines[n - 1].c = (F - A * beta[n - 2]) / (C + A * alpha[n - 2]);
        for (int i = n - 2; i > 0; --i)
            splines[i].c = alpha[i] * splines[i + 1].c + beta[i];
        delete[] beta;
        delete[] alpha;
        for (int i = n - 1; i > 0; --i) {
            double h_i = data[i].x - data[i - 1].x;
            splines[i].d = (splines[i].c - splines[i - 1].c) / h_i;
            splines[i].b = h_i * (2. * splines[i].c + splines[i - 1].c) / 6. + (data[i].y - data[i - 1].y) / h_i;
        }
    }

    double interpolate(double x) const {
        if (!splines)
            return -1;
        spline_tuple *s;
        if (x <= splines[0].x)
            s = splines + 1;
        else if (x >= splines[n - 1].x)
            s = splines + n - 1;
        else {
            int i = 0, j = n - 1;
            while (i + 1 < j) {
                int k = i + (j - i) / 2;
                if (x <= splines[k].x)
                    j = k;
                else
                    i = k;
            }
            s = splines + j;
        }
        double dx = (x - s->x);
        return s->a + (s->b + (s->c / 2. + s->d * dx / 6.) * dx) * dx;
    }

    ~cubic_spline() {
        free_mem();
    }
};

class IBicubic {
    virtual void build(dot3d **A, int n, int m) = 0;

    virtual double interpolate(dot2d X) = 0;
};

class dim_exp : public IBicubic {
private:
    struct y_spline {
        double y;
        cubic_spline ci;
    };
    int n;
    y_spline *data;

    void free_mem() {
        delete[] data;
        data = NULL;
    }

public:
    dim_exp() : data(NULL), n(0) {
    }

    void build(dot3d **A, int n, int m) {
        this->n = n;
        data = new y_spline[n + 1];
        dot2d *arr = new dot2d[m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                arr[j] = {A[i][j].x, A[i][j].z};
            }
            data[i].ci.build_spline(arr, m);
            data[i].y = A[i][0].y;
        }
        delete[] arr;
    }

    double interpolate(dot2d X) {
        dot2d *arr = new dot2d[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = {data[i].y, data[i].ci.interpolate(X.x)};
        }
        data[n].ci.build_spline(arr, n);
        delete[] arr;
        return data[n].ci.interpolate(X.y);
    }

    ~dim_exp() {
        free_mem();
    }
};

class bicubic_spline : public IBicubic {
private:
    struct spline_tuple {
        double a[4][4];
        dot2d anc;
    };
    spline_tuple **splines;
    int n;
    int m;

    void free_mem() {
        for (int i = 0; i < n; ++i) {
            delete[] splines[i];
        }
        delete[] splines;
        splines = NULL;
    }

public:
    bicubic_spline() : splines(NULL), n(0), m(0){
    }

    void build(dot3d **A, int n, int m) {
        if (n < 4 || m < 4) {
            return;
        }
        splines = new spline_tuple *[n - 3];
        for (int i = 0; i < n - 3; ++i) {
            splines[i] = new spline_tuple[m - 3];
        }
        this->n = n - 3;
        this->m = m - 3;
        int M[16][16] = {{0,  0,   0,   0,  0,   36,  0,   0,  0,   0,   0,   0,  0,  0,  0,  0},
                         {0,  -12, 0,   0,  0,   -18, 0,   0,  0,   36,  0,   0,  0,  -6, 0,  0},
                         {0,  18,  0,   0,  0,   -36, 0,   0,  0,   18,  0,   0,  0,  0,  0,  0},
                         {0,  -6,  0,   0,  0,   18,  0,   0,  0,   -18, 0,   0,  0,  6,  0,  0},
                         {0,  0,   0,   0,  -12, -18, 36,  -6, 0,   0,   0,   0,  0,  0,  0,  0},
                         {4,  6,   -12, 2,  6,   9,   -18, 3,  -12, -18, 36,  -6, 2,  3,  -6, 1},
                         {-6, -9,  18,  -3, 12,  18,  -36, 6,  -6,  -9,  18,  -3, 0,  0,  0,  0},
                         {2,  3,   -6,  1,  -6,  -9,  18,  -3, 6,   9,   -18, 3,  -2, -3, 6,  -1},
                         {0,  0,   0,   0,  18,  -36, 18,  0,  0,   0,   0,   0,  0,  0,  0,  0},
                         {-6, 12,  -6,  0,  -9,  18,  -9,  0,  18,  -36, 18,  0,  -3, 6,  -3, 0},
                         {9,  -18, 9,   0,  -18, 36,  -18, 0,  9,   -18, 9,   0,  0,  0,  0,  0},
                         {-3, 6,   -3,  0,  9,   -18, 9,   0,  -9,  18,  -9,  0,  3,  -6, 3,  0},
                         {0,  0,   0,   0,  -6,  18,  -18, 6,  0,   0,   0,   0,  0,  0,  0,  0},
                         {2,  -6,  6,   -2, 3,   -9,  9,   -3, -6,  18,  -18, 6,  1,  -3, 3,  -1},
                         {-3, 9,   -9,  3,  6,   -18, 18,  -6, -3,  9,   -9,  3,  0,  0,  0,  0},
                         {1,  -3,  3,   -1, -3,  9,   -9,  3,  3,   -9,  9,   -3, -1, 3,  -3, 1}};
        double *phi = new double[16];
        for (int _i = 0; _i < n - 3; ++_i) {
            for (int _j = 0; _j < m - 3; ++_j) {
                for (int i = -1; i < 3; ++i) {
                    for (int j = -1; j < 3; ++j) {
                        phi[(i + 1) * 4 + j + 1] = A[_j + j + 1][_i + i + 1].z;
                    }
                }
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        double res = 0;
                        for (int k = 0; k < 16; ++k) {
                            res += phi[k] * M[i * 4 + j][k];
                        }
                        splines[_i][_j].a[i][j] = res / 36.0;
                    }
                }
                splines[_i][_j].anc = {A[_i][_j].x, A[_i][_j].y};
            }
        }
        delete[] phi;
    }

    double interpolate(dot2d X) {
        if (!splines)
            return -1;
        spline_tuple s;
        if (X.x <= splines[0][0].anc.x || X.y <= splines[0][0].anc.y)
            s = splines[0][0];
        else if (X.x >= splines[0][m - 1].anc.x)
            s = splines[0][m - 1];
        else if (X.y >= splines[n - 1][0].anc.y)
            s = splines[0][n - 1];
        else {
            int i = 0, j = n - 1;
            while (i + 1 < j) {
                int k = i + (j - i) / 2;
                if (X.y <= splines[k][0].anc.y)
                    j = k;
                else
                    i = k;
            }
            int i2 = 0, j2 = m - 1;
            while (i2 + 1 < j2) {
                int k = i2 + (j2 - i2) / 2;
                if (X.x <= splines[j][k].anc.x)
                    j2 = k;
                else
                    i2 = k;
            }
            s = splines[j][j2];
        }
        double res = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res += s.a[i][j] * pow(X.y-s.anc.x-1, i) * pow(X.x-s.anc.y-1, j);
            }
        }
        return res;
    }

    ~bicubic_spline() {
        free_mem();
    }
};

int main() {
    //input grid
    dot3d data[4][4] = {{{0., 0., 0.},  {1., 0., 2.3}, {2., 0., 4.},  {3., 0., 0.}},
                        {{0., 1., 6.},  {1., 1., 3.},  {2., 1., 5.1}, {3., 1., 1.8}},
                        {{0., 2., 4.},  {1., 2., 2.},  {2., 2., 1.3}, {3., 2., 5.}},
                        {{0., 3., 4.8}, {1., 3., 4.},  {2., 3., 1.9}, {3., 3., 3.2}}};
    dot3d **arr;
    arr = new dot3d *[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = new dot3d[4];
        for (int j = 0; j < 4; ++j) {
            arr[i][j] = data[i][j];
        }
    }
    dim_exp bci;
    bci.build(arr, 4, 4);
    bicubic_spline bcsi;
    bcsi.build(arr, 4, 4);
    cout << setw(20) << "Splice " << setw(20) << "Dim. Exten" << setw(20) << "Delta" << endl;
    for (float i = 1.0; i < 2.0; i += 0.2f){
        for (float j = 1.0; j < 2.0; j += 0.2f){
            dot2d test = {i, j};
            double dimext = bci.interpolate(test);
            double splice = bcsi.interpolate(test);
            cout << fixed << setprecision(5);
            cout << setw(20) << splice << setw(20) << dimext << setw(20) << fabs(splice-dimext) << endl;
        }
    }

    for (int i = 0; i < 4; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}
