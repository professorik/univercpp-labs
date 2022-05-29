#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define ll long long
#define elem pair<ll, int>

vector<elem> readElements(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open())
        throw exception("File cannot be opened");

    vector<elem> res;
    for (int i = 0, val; !fin.eof(); ++i) {
        fin >> val;
        res.emplace_back(val, i);
    }
    fin.close();
    return res;
}

int main() {
    vector<elem> vec;
    map<ll, vector<int>> m;
    try {
        vec = readElements("containers.txt");
    } catch (exception &err) {
        cout << err.what() << endl;
    }
    for (elem i: vec) {
        if (m.find(i.first) != m.end()){
            m[i.first].push_back(i.second);
        }else{
            m[i.first] = vector<int> {i.second};
        }
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        if (binary_search(m[vec[i].first].begin(), m[vec[i].first].end(), i)){
            cout << vec[i].second << endl;
        }
    }
    return 0;
}