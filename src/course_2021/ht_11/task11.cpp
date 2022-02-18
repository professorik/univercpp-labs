#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <limits>
#include <thread>
#include <time.h>

typedef struct stars_base {
    double x;
    double y;
    double dx;
    double dy;
} stars_base;

typedef struct matrix_stars: public stars_base {
    double med_dx;
    double med_dy;
    int count;
    int fit_count;
} matrix_stars;

static matrix_stars map[1000][1000];

static int get_index(double x, double max, double min, int n) {
    if (x > max) { return n - 1; }
    else if (x < min) { return 0; }
    else { return (int) ((x - min) / (max - min) * (n - 1)); }
}

static double median(std::vector<double> &pDouble, int n) {
    std::sort(pDouble.begin(), pDouble.end());
    return n & 1? pDouble[n/2]: (pDouble[n/2] + pDouble[(n-1)/2])/2.0;
}

static int create_map(int start_x, int start_y, int nx, int ny, const int sx, const int sy, int min_count) {
    int i, j;
    const int max_n = (2 * sx + 1) * (2 * sy + 1);
    for (i = start_x; i < nx; ++i) {
        for (j = start_y; j < ny; ++j) {
            int x = i - sx;
            int y = j - sy;
            int t, n = 0;
            int all_n = 0;
            std::vector<double> arr_pmRA(max_n);
            std::vector<double> arr_pmDEC(max_n);
            if (x < 0) { x = 0; }
            if (y < 0) { y = 0; }
            t = y;
            while (x <= i + sx && x < nx) {
                y = t;
                while (y <= j + sy && y < ny) {
                    if (map[x][y].count != 0) {
                        arr_pmRA[n] = map[x][y].dx;
                        arr_pmDEC[n] = map[x][y].dy;
                        all_n += map[x][y].count;
                        ++n;
                    }
                    ++y;
                }
                ++x;
            }
            if (n >= min_count) {
                map[i][j].med_dx = median(arr_pmRA, n);
                map[i][j].med_dy = median(arr_pmDEC, n);
                map[i][j].fit_count = all_n;
            }
        }
    }
    return 0;
}

using namespace std;

//size of window
const int sx = 5;
const int sy = 5;
double max_x, min_x, max_y, min_y;
int nx, ny;

void skipLine(FILE *f) {
    while (!feof(f)) {
        if (fgetc(f) == '\n') { break; }
    }
}

void readData(const char *input, vector<stars_base> &stars) {
    FILE *f = fopen(input, "r");
    if (!f) {
        cout << "Error: cannot open the file" << endl;
        return;
    }
    stars_base temp;
    cout << "Reading data..." << endl;
    while (!feof(f)) {
        if (fscanf(f, "%lf %lf %lf %lf", &temp.x, &temp.y, &temp.dx, &temp.dy) == 4) {
            stars.push_back(temp);
            max_x = max(max_x, temp.x);
            max_y = max(max_y, temp.y);
            min_x = min(min_x, temp.x);
            min_y = min(min_y, temp.y);
        }
        skipLine(f);
    }
    cout << flush << "loaded " << stars.size() << " objects!" << endl;
    fclose(f);
}

void writeData(const char *output, vector<stars_base> &stars) {
    FILE *f = fopen(output, "w");
    if (!f) {
        cout << "Error: cannot open the file" << endl;
        return;
    }
    cout << "Writing data..." << endl;
    for (int i = 0; i < stars.size(); ++i) {
        fprintf(f, "%4.8g\t%4.8g\t%4.8g\t%4.8g\n", stars[i].x, stars[i].y, stars[i].dx, stars[i].dy);
    }
    cout << "loaded " << stars.size() << " objects" << endl;
    fclose(f);
}

int main() {
    min_x = min_y = numeric_limits<double>::max();
    max_x = max_y = -min_x;
    nx = ny = 1000;
    vector<stars_base> data;
    readData("D:/univercpp/src/ht_11/psc_gaia_318.txt", data);
    cout << "Initializing map data" << endl;
    for (int i = 0, xx, yy; i < data.size(); ++i) {
        xx = get_index(data[i].x, max_x, min_x, nx);
        yy = get_index(data[i].y, max_y, min_y, ny);
        map[xx][yy].count++;
        map[xx][yy].x += (data[i].x - map[xx][yy].x) / map[xx][yy].count;
        map[xx][yy].y += (data[i].y - map[xx][yy].y) / map[xx][yy].count;
        map[xx][yy].dx += (data[i].dx - map[xx][yy].dx) / map[xx][yy].count;
        map[xx][yy].dy += (data[i].dy - map[xx][yy].dy) / map[xx][yy].count;
    }
    cout << "Filtering map" << endl;
    clock_t tStart = clock();
    const int kx = 2, ky = 2; //kx,ky > 0
    thread th[kx*ky];
    for (int i = 0; i < kx; ++i){
        for (int j = 0; j < ky; ++j) {
            th[i*ky + j] = thread(create_map, i*nx/kx, j*ny/ky, (i+1)*nx/kx, (j+1)*ny/ky, sx, sy, 0);
        }
    }
    for (int i = 0; i < kx*ky; ++i) {
        th[i].join();
    }
    cout << "Filtering execution time: " << clock() - tStart << endl;
    for (int i = 0, xx, yy; i < data.size(); ++i) {
        xx = get_index(data[i].x, max_x, min_x, nx);
        yy = get_index(data[i].y, max_y, min_y, ny);
        if (map[xx][yy].fit_count != 0) {
            data[i].dx -= map[xx][yy].med_dx;
            data[i].dy -= map[xx][yy].med_dy;
        }
    }
    writeData("D:/univercpp/src/ht_11/res.txt", data);
}


/*
 * 27666 - one thread
 * 18212 - two threads
 * 12424 - four threads
 */