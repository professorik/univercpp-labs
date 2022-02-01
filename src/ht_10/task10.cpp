#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iomanip>

using namespace std;

typedef unsigned int ui;

struct star {
    double ra, dec;
    float plx, mura, mudec, hpmag;


    friend ostream &operator<<(ostream &out, const star &s) {
        out << fixed << setprecision(6) << s.ra << " " << s.dec << " " << s.plx << " " << s.mura
            << " " << s.mudec << " " << s.hpmag;
        return out;
    }
};

class comparator {
private:
    int field;
    int order;
public:
    comparator() {}

    comparator(const string &field, const string &order) {
        this->order = 1;
        if (order == "i")
            this->order = 1;
        else if (order == "d")
            this->order = -1;
        else
            cerr << "Incorrect order (only i and d are allowed). It's using \"i\" by default." << endl;
        this->field = -1;
        string names[6] = {"ra", "dec", "plx", "mura", "mudec", "hpmag"};
        for (int i = 0; i < 6; ++i) {
            if (names[i] == field) {
                this->field = i;
                break;
            }
        }
        if (this->field == -1) {
            this->field = 0;
            cerr << "Incorrect field ([";
            //from c++11
            for (const string &s: names) cerr << "\"" << s << "\" ";
            cerr << "] are allowed). It's using \"ra\" by default." << endl;
        }
    }

    bool operator()(star a, star b) const {
        switch (field) {
            case 0:
                return (a.ra - b.ra) * order < 0;
            case 1:
                return (a.dec - b.dec) * order < 0;
            case 2:
                return (a.plx - b.plx) * order < 0;
            case 3:
                return (a.mura - b.mura) * order < 0;
            case 4:
                return (a.mudec - b.mudec) * order < 0;
            default:
                return (a.hpmag - b.hpmag) * order < 0;
        }
    }
};

void bubble_sort(vector<star> &v, int l, int r, comparator cmp) {
    for (int i = 0; i < r - l; ++i) {
        bool fl = true;
        for (int j = 0; j < r - l - i; ++j) {
            if (cmp.operator()(v[j + l + 1], v[j + l])) {
                swap(v[j + l], v[j + l + 1]);
                fl = false;
            }
        }
        if (fl) break;
    }
}

int partition(vector<star> &v, int l, int r, comparator cmp) {
    star e = v[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (cmp.operator()(v[i], e)) i++;
        while (cmp.operator()(e, v[j])) j--;
        if (i >= j) break;
        swap(v[i++], v[j--]);
    }
    return j;
}

int median(vector<star> &v, int l, int r, comparator cmp) {
    int m = (l + r) / 2;
    if (cmp.operator()(v[l], v[r]) && !cmp.operator()(v[l], v[m])) {
        return l;
    } else if (cmp.operator()(v[m], v[r]) && !cmp.operator()(v[m], v[l])) {
        return m;
    } else {
        return r;
    }
}

void quicksort(vector<star> &v, int l, int r, comparator cmp) {
    if (r - l <= 10) {
        bubble_sort(v, l, r, cmp);
        return;
    }
    swap(v[median(v, l, r, cmp)], v[(l + r) / 2]);
    int i = partition(v, l, r, cmp);
    quicksort(v, l, i, cmp);
    quicksort(v, i + 1, r, cmp);
}

vector<star> Stars;

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
    star temp;
    while (!feof(f)) {
        if (fscanf(f, "%lf %lf %f %f %f %f",
                   &temp.ra, &temp.dec, &temp.plx, &temp.mura, &temp.mudec, &temp.hpmag) == 6) {
            Stars.push_back(temp);
        } else { skipLine(f); }
    }
    cout << "loaded " << Stars.size() << " objects" << endl;
    fclose(f);
}

void writeData(const char *output) {
    FILE *f = fopen(output, "w");
    if (!f) {
        cout << "Error: cannot open the file" << endl;
        return;
    }
    fprintf(f, "%s", "RA\tDEC\tPlx\tMuRA\tMuDE\tHpmag\n");
    for (int i = 0; i < Stars.size(); ++i) {
        fprintf(f, "%4.8g\t%4.8g\t%4.8g\t%4.8g\t%4.8g\t%4.8g\n", Stars[i].ra, Stars[i].dec, Stars[i].plx, Stars[i].mura,
                Stars[i].mudec, Stars[i].hpmag);
    }
    cout << "loaded " << Stars.size() << " objects" << endl;
    fclose(f);
}

int main(int argc, char **argv) {
    if (argc == 5) {
        comparator cmp(argv[2], argv[3]);
        readData(argv[1]);
        ui start_time, end_time;
        pair<string, ui> times[3];
        vector<star> tempStars = Stars;
        vector<star> tempStars2 = Stars;
        start_time = clock();
        sort(tempStars.begin(), tempStars.end(), cmp);
        end_time = clock();
        times[0] = make_pair("sort", end_time - start_time);

        start_time = clock();
        quicksort(Stars, 0, Stars.size() - 1, cmp);
        end_time = clock();
        times[1] = make_pair("qsort", end_time - start_time);

        start_time = clock();
        bubble_sort(tempStars2, 0, tempStars2.size() / 100, cmp);
        end_time = clock();
        times[2] = make_pair("bubble~", 10000 * (end_time - start_time));
        for (int i = 0; i < 3; ++i) {
            cout << setw(10) << times[i].first << setw(10) << times[i].second << endl;
        }
        writeData(argv[4]);
    } else {
        cerr << "Incorrect input";
    }
    return 0;
}