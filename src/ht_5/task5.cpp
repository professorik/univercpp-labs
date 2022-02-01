#include<iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class matrix {
private:
    double **data;
    int n, m;
public:
    matrix(int n, int m) : n(n), m(m) {
        data = new double *[n];
        for (int i = 0; i < n; ++i)
            data[i] = new double[m];
    }

    matrix(const matrix &other): matrix(other.n, other.m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    void get_data() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> data[i][j];
    }

    void show_data() {
        cout << fixed << showpoint << setprecision(3);
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                cout << data[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << flush;
    }

    matrix operator+(const matrix &) const;
    matrix operator-(const matrix &) const;
    matrix operator*(const matrix &) const;
    matrix operator*(const double &) const;
    matrix operator/(const matrix &) const;
    matrix operator/(const double &) const;

    static double _det(const matrix &a){
        if (a.n != a.m){
            cout << "Impossible to calculate" << endl;
            return 0;
        }
        double res = 0;
        if (a.n == 1) return a.data[0][0];
        if (a.n == 2) return a.data[0][0]*a.data[1][1]-a.data[1][0]*a.data[0][1];
        for (int i = 0; i < a.m; ++i){
            matrix temp(a.n-1, a.m-1);
            for (int j = 1; j < a.n; ++j){
                for (int k = 0; k < a.m; ++k){
                    if (k < i){
                        temp.data[j-1][k] = a.data[j][k];
                    }else if (k > i){
                        temp.data[j-1][k-1] = a.data[j][k];
                    }
                }
            }
            res += (i & 1? -1: 1) * a.data[0][i]*_det(temp);
        }
        return res;
    }

    static matrix _trans(const matrix &a){
        matrix res(a.m, a.n);
        for (int i = 0; i < a.n; ++i){
            for (int j = 0; j < a.m; ++j){
                res.data[j][i] = a.data[i][j];
            }
        }
        return res;
    }

    static matrix _inverse(const matrix &a){
        double deter = _det(a);
        if (a.n != a.m || fabs(deter) < 1e-3){
            cout << "Impossible to calculate" << endl;
            return matrix(0,0);
        }
        matrix trans = _trans(a);
        matrix res(a.n, a.n);
        if (a.n == 1){
            res.data[0][0] = 1/trans.data[0][0];
            return res;
        }
        for (int i = 0; i < trans.n; ++i){
            for (int j = 0; j < trans.m; ++j){
                matrix temp(trans.n-1, trans.m-1);
                for (int k = 0; k < trans.n; ++k){
                    for (int l = 0; l < trans.m; ++l){
                        if (k == i || l == j) continue;
                        int y = k < i? k : k - 1;
                        int x = l < j? l : l - 1;
                        temp.data[y][x] = trans.data[k][l];
                    }
                }
                res.data[i][j] = ((i+j) & 1? -1: 1)*_det(temp);
            }
        }
        return res/deter;
    }


    ~matrix() {
        if (data) {
            for (int i = 0; i < n; ++i)
                if (data[i]) delete data[i];
            delete data;
        }
    }
};

matrix matrix::operator+(const matrix &a) const{
    if (a.n != n || a.m != m){
        cout << "Error: matrix sizes must be equal" << endl;
        return matrix(0,0);
    }
    matrix res(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res.data[i][j] = data[i][j] + a.data[i][j];
        }
    }
    return res;
}

matrix matrix::operator-(const matrix &a) const{
    if (a.n != n || a.m != m){
        cout << "Error: matrix sizes must be equal" << endl;
        return matrix(0,0);
    }
    matrix res(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res.data[i][j] = data[i][j] - a.data[i][j];
        }
    }
    return res;
}

matrix matrix::operator*(const matrix &a) const{
    if (m != a.n){
        cout << "It's not possible to multiple" << endl;
        return matrix(0,0);
    }
    matrix res(n, a.m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a.m; ++j) {
            res.data[i][j] = 0;
            for (int k = 0; k < m; ++k){
                res.data[i][j] += data[i][k] * a.data[k][j];
            }
        }
    }
    return res;
}

matrix matrix::operator*(const double &c) const{
    matrix res(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j){
            res.data[i][j] = c*data[i][j];
        }
    }
    return res;
}

matrix matrix::operator/(const matrix& a) const{
    if (a.n != a.m || m != a.n || fabs(_det(a)) < 1e-3){
        cout << "It's not possible to divide" << endl;
        return matrix(0,0);
    }
    matrix res(n, m);
    matrix temp = _inverse(a);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < temp.m; ++j) {
            res.data[i][j] = 0;
            for (int k = 0; k < m; ++k){
                res.data[i][j] += data[i][k] * temp.data[k][j];
            }
        }
    }
    return res;
}

matrix matrix::operator/(const double &c) const{
    if (fabs(c) < 1e-3){
        cout << "It's not possible to divide" << endl;
        return matrix(0,0);
    }
    matrix res(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j){
            res.data[i][j] = data[i][j]/c;
        }
    }
    return res;
}

matrix operator*(const double &c, const matrix &a){
    return a*c;
}

matrix operator/(const double &c, const matrix &a){
    return c*matrix::_inverse(a);
}

int main() {
    cout << "Enter n and m for matrix" << endl;
    int n, m;
    cin >> n >> m;
    matrix A(n, m);
    cout << "Enter data for A matrix" << endl;
    A.get_data();
    matrix B(m,n);
    cout << "Enter data for B matrix" << endl;
    B.get_data();
    (A+A).show_data();
    (A-A).show_data();
    (3.0*A).show_data();
    (A*0.5).show_data();
    (A*A).show_data();
    (A/A).show_data();
    (A/2).show_data();
    (2/A).show_data();
    (3*A-(A)*(A/A)).show_data();
    matrix C=A+B;
    matrix D=A+B-C*(B-A);
    D.show_data();
    return 0;
}
