#include "Square.h"
#include "Circle.h"
#include "Equilateral.h"
#include <vector>
#include <cassert>
#include <set>

using namespace std;

typedef pair<set<int>, set<int>> pss;

void deepSearch(vector<pss> &res, vector<Figure *> &figures, int dest, int index){
    if (figures[dest]->isOverlapping(figures[index])){
        res[dest].first.insert(index);
        res[dest].first.insert(res[index].first.begin(), res[index].first.end());
        for (int i: res[index].second){
            deepSearch(res, figures, dest, i);
        }
    } else {
        res[dest].second.insert(index);
        res[dest].second.insert(res[index].second.begin(), res[index].second.end());
        for (int i: res[index].first){
            deepSearch(res, figures, dest, i);
        }
    }
}

int main() {
    vector<Figure *> figures;
    figures.push_back(new Square(2));
    figures.push_back(new Circle(1));
    figures.push_back(new Circle(3.4));
    figures.push_back(new Square(54));
    figures.push_back(new Rectangle(3, 4));
    figures.push_back(new Equilateral(2));

    assert(figures[0]->calcArea() == 4 && figures[0]->calcPerimeter() == 8);
    assert(abs(figures[1]->calcArea() - 3.1415f) < 1e-3 && abs(figures[1]->calcPerimeter() - 6.283f) < 1e-3);
    assert(figures[4]->calcArea() == 12 && figures[4]->calcPerimeter() == 14);
    assert(abs(figures[5]->calcArea() - sqrt(3)) < 1e-3 && figures[5]->calcPerimeter() == 6);

    assert(abs(figures[0]->getRadiusFactor() - sqrt(2)) < 1e-3);
    assert(figures[1]->getRadiusFactor() == 1);
    assert(abs(figures[4]->getRadiusFactor() - 2.5) < 1e-6);
    assert(abs(figures[5]->getRadiusFactor() - 2 / sqrt(3)) < 1e-3);

    //first - overlapping, second - not
    vector<pss> res(figures.size());
    for (int i = figures.size() - 2; i >= 0; --i) {
        deepSearch(res, figures, i, i + 1);
    }

    for (int i = 0; i < figures.size(); ++i){
        figures[i]->printInfo();
        cout << "Overlapping: ";
        if (res[i].first.empty()) cout << "empty";
        for (int j: res[i].first){
            cout << j << " ";
        }
        cout << "\nNot full: ";
        if (res[i].second.empty()) cout << "empty";
        for (int j: res[i].second){
            cout << j << " ";
        }
        cout << "\n--------------" << endl;
    }
    return 0;
}