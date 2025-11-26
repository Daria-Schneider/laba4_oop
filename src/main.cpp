#include <iostream>
#include <memory>
#include "pentagon.h"
#include "hexagon.h"
#include "octagon.h"
#include "array.h"

using namespace std;

int main() {
    Array<shared_ptr<Figure<double>>> figures;
    
    cout << "Enter number of figures: ";
    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cout << "Figure " << i + 1 << " type (1-pentagon, 2-hexagon, 3-octagon): ";
        int type;
        cin >> type;
        
        shared_ptr<Figure<double>> fig;
        
        if (type == 1) {
            fig = make_shared<Pentagon<double>>();
            cout << "Enter 5 points for pentagon (x y):" << endl;
        } else if (type == 2) {
            fig = make_shared<Hexagon<double>>();
            cout << "Enter 6 points for hexagon (x y):" << endl;
        } else if (type == 3) {
            fig = make_shared<Octagon<double>>();
            cout << "Enter 8 points for octagon (x y):" << endl;
        } else {
            cout << "Wrong type, skip" << endl;
            i--;
            continue;
        }
        
        for (size_t j = 0; j < fig->vertex_count(); ++j) {
            Point<double> p;
            cin >> p;
            fig->vertex(j) = p;
        }
        
        figures.push_back(fig);
    }
    
    cout << "\nAll figures:" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Figure " << i << ": " << *figures[i] << endl;
        cout << "Area: " << figures[i]->area() << endl;
        cout << "Center: " << figures[i]->center() << endl;
        cout << endl;
    }
    
    double total = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += static_cast<double>(*figures[i]);
    }
    cout << "Total area: " << total << endl;
    
    if (figures.size() > 0) {
        cout << "Enter index to delete: ";
        size_t idx;
        cin >> idx;
        if (idx < figures.size()) {
            figures.erase(idx);
            cout << "Deleted" << endl;
        }
    }
    
    cout << "Remaining figures: " << figures.size() << endl;
    
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    cout << "Array<int> size: " << arr1.size() << endl;
    
    Array<shared_ptr<Figure<double>>> arr2;
    cout << "Array<shared_ptr<Figure>> size: " << arr2.size() << endl;
    
    return 0;
}