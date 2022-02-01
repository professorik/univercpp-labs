#include <cmath>
#include <cstdio>
#include <cstdlib>

class mnk {
private:
    int m;
    double **C;
    double **Cinv;
    double *Y;
    double *A;
    double *EA;

    void creat_sum(double *, double y, int l);

public:
    mnk(int mm) {
        m = mm;
        A = new double[m];
        EA = new double[m];
        Y = new double[m];
        C = new double *[m];
        Cinv = new double *[m];
        for (int i = 0; i < m; ++i) {
            C[i] = new double[m];
            Cinv[i] = new double[m];
        }
    }

    void get_null();

    void get_null_A();

    void inversion();

    void mulip_matrix_vector();

    int calc_errors(double *K, double *EK, int pmax, double sigm, double student);

    void get_fit(double *P, int pmax);

    //methods for array
    int put_data_array(double **array_i, int n, int p, double sigm, double *K);

    double calc_sigm(double **data, int n, int p, double sigm_old, double *K);

    ~mnk() {
        delete[]A;
        delete[]EA;
        delete[]Y;
        for (int i = 0; i < m; ++i) {
            delete[]C[i];
            delete[]Cinv[i];
        }
        delete[]C;
        delete[]Cinv;
    }
};

void mnk::get_null() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = 0;
            Cinv[i][j] = 0;
        }
        Y[i] = 0;
        EA[i] = 0;
    }
}

void mnk::get_null_A() { for (int i = 0; i < m; ++i) A[i] = 0; }

void mnk::get_fit(double *P, int pmax) {
    int k = 0;
    for (int i = 0; i < pmax; ++i) {
        if (P[i] != 0.0) {
            P[i] = A[k];
            k++;
        } else { P[i] = 0; }
    }
}

void mnk::creat_sum(double *L, double y, int l) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++) {
            C[i][j] += L[i] * L[j];
        }
        Y[i] += L[i] * y;
    }
}

void mnk::inversion() {
    double **ct = new double *[m];
    for (int i = 0; i < m; ++i) {
        ct[i] = new double[m];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j)
                Cinv[i][j] = 1.0;
            else
                Cinv[i][j] = 0;
            ct[i][j] = C[i][j];
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            Cinv[i][j] /= ct[i][i];
        }
        for (int j = m - 1; j >= i; --j) {
            ct[i][j] /= ct[i][i];
        }
        for (int j = 0; j < m; ++j) {
            if (j == i) continue;
            for (int k = m - 1; k > i; --k) {
                Cinv[j][k] -= Cinv[i][k] * ct[j][i];
                ct[j][k] -= ct[i][k] * ct[j][i];
            }
            for (int k = i; k >= 0; --k) {
                Cinv[j][k] -= Cinv[i][k] * ct[j][i];
            }
            ct[j][i] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        delete[]ct[i];
    }
    delete[]ct;
}

void mnk::mulip_matrix_vector() {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            A[i] += Cinv[i][j] * Y[j];
}

int mnk::calc_errors(double *K, double *EK, int pmax, double sigm, double student) {
    int k = 0;
    int n = 0;
    for (int i = 0; i < pmax; ++i) {
        if (K[i] != 0.0) {
            EA[k] = sigm * sqrt(Cinv[k][k]);
            if (fabs(A[k]) < student * EA[k]) {
                K[i] = 0.0;
            } else {
                K[i] = A[k];
                EK[i] = EA[k];
                ++n;
            }
            k++;
        }
    }
    return n;
}

int mnk::put_data_array(double **data, int n, int p, double sigm, double *K) {
    double *L = new double[m];
    double y;
    int count = 0;
    double FUN = 0;
    for (int i = 0; i < n; ++i) {
        int l = 0;
        if (K[0] != 0.0) {
            FUN = K[0];
            L[0] = 1.0;
            l++;
        }
        for (int j = 0; j < p - 1; ++j) {
            if (K[j + 1] != 0.0) {
                L[l] = data[i][j];
                FUN += K[j + 1] * L[l];
                l++;
            }
        }
        y = data[i][p - 1];
        if (fabs(FUN - y) <= 3.0 * sigm) {
            creat_sum(L, y, l);
            count++;
        }
    }
    delete[]L;
    return count;
}

double mnk::calc_sigm(double **data, int n, int p, double sigm_old, double *K) {
    double *L = new double[m];
    double y;
    int count = 0;
    double FUN = 0;
    double sigm = 0;
    int l = 0;
    for (int i = 0; i < n; ++i) {
        if (K[0] != 0.0) {
            FUN = K[0];
            L[0] = 1.0;
            l = 1;
        } else {
            FUN = 0;
            l = 0;
        }
        for (int j = 0; j < p - 1; ++j) {
            if (K[j + 1] != 0.0) {
                L[l] = data[i][j];
                FUN += K[j + 1] * L[l];
                l++;
            }
        }
        y = data[i][p - 1];
        if (fabs(FUN - y) <= 3.0 * sigm_old) {
            sigm += (FUN - y) * (FUN - y);
            count++;
        }
    }
    delete[]L;
    return sqrt(sigm / (count - l));
}

void calc_mnk(double **data, int n, double *P, double *EP, int pmax) {
    double sigma = 1000000000.0;
    double temp_sigma = 1.0;
    int p = pmax;
    for (int i = 0; i < pmax; ++i) P[i] = 1.0;
    do {
        mnk obj(p);
        obj.get_null();
        temp_sigma = sigma;
        int count = obj.put_data_array(data, n, pmax, temp_sigma, P);
        fprintf(stderr, "load %d data\n", count);
        obj.inversion();
        obj.get_null_A();
        obj.mulip_matrix_vector();
        obj.get_fit(P, pmax);
        sigma = obj.calc_sigm(data, n, pmax, temp_sigma, P);
        p = obj.calc_errors(P, EP, pmax, sigma, 3.0);
        for (int i = 0; i < pmax; ++i)
            fprintf(stderr, "K[%d]=%lf+-%lf\n", i, P[i], EP[i]);
        fprintf(stderr, "dispersion=%lf\n", sigma);
    } while (sigma < temp_sigma);
}

void skipLine(FILE *f) {
    while (!feof(f)) {
        if (fgetc(f) == '\n') { break; }
    }
}

int main(int argc, char **argv) {
    if (argc == 3) {
        char *filename = argv[1];
        int column = atoi(argv[2]);
        int degree = column;
        FILE *f = fopen(filename, "r");
        if (!f) {
            fprintf(stderr, "Can not open file %s\n", filename);
            return -1;
        }
        double **data = new double *[1000000];
        for (int i = 0; i < 1000000; ++i)
            data[i] = new double[degree];
        double *P = new double[degree];
        double *EP = new double[degree];
        int count = 0;
        while (!feof(f)) {
            for (int i = 0; i < degree; ++i) {
                if (fscanf(f, "%lf", &data[count][i]) != 1) {
                    skipLine(f);
                    break;
                }
            }
            count++;
        }
        printf("load %d data\n", count);
        calc_mnk(data, count - 1, P, EP, degree);
        for (int i = 0; i < degree; ++i)
            printf("P=%lf+-%lf\n", P[i], EP[i]);
        for (int i = 0; i < degree; ++i)
            delete[] data[i];
        delete[] P;
        delete[] EP;
    }
    return 0;
}