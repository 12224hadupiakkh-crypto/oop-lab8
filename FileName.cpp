#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

struct AbsMinComparer {
    bool operator()(int a, int b) const {
        return abs(a) < abs(b);
    }
};

class RangeRemover {
private:
    int lower;
    int upper;
public:
    RangeRemover(int a, int b) : lower(a), upper(b) {}

    bool operator()(int val) const {
        return (val >= lower && val <= upper);
    }
};

void print_list(const list<int>& l, const string& title) {
    cout << "\n--- " << title << " ---\n";
    for (int val : l) {
        cout << setw(4) << val;
    }
    cout << endl;
}

void execute_task_list(list<int> l, int a, int b) {
    int initial_size = l.size();

    cout << "\n=======================================================\n";
    cout << "  Input list (N=" << initial_size << "):";
    print_list(l, "Initial data");

    auto it_min_abs = min_element(l.begin(), l.end(), AbsMinComparer());

    if (it_min_abs != l.end()) {
        int index_min_abs = distance(l.begin(), it_min_abs);
        cout << "\n1. Index of the minimum by absolute value element: "
            << index_min_abs
            << " (Value: " << *it_min_abs << ")";
        cout << "\n   (Indexes start from 0, element number starts from 1)";
    }
    else {
        cout << "\n1. The list is empty.";
    }

    auto it_first_neg = find_if(l.begin(), l.end(),
        [](int val) { return val < 0; });

    long long sum_abs = 0;

    if (it_first_neg != l.end()) {
        auto it_start = next(it_first_neg);

        sum_abs = accumulate(it_start, l.end(), 0LL,
            [](long long acc, int val) {
                return acc + abs(val);
            });

        cout << "\n\n2. Sum of absolute values of elements after the first negative ("
            << *it_first_neg << "): " << sum_abs;
    }
    else {
        cout << "\n\n2. There are no negative elements in the list. Sum: 0";
    }

    cout << "\n\n3. List compression: removing elements in the range [" << a << ", " << b << "]";

    l.remove_if(RangeRemover(a, b));

    int current_size = l.size();
    int elements_to_add = initial_size - current_size;

    for (int i = 0; i < elements_to_add; ++i) {
        l.push_back(0);
    }

    print_list(l, "List after compression and filling with zeros");

    cout << "\n=======================================================\n";
}

int main() {
    setlocale(LC_ALL, "English");

    // Set 1: N=10, D = [2, 10]
    list<int> l1 = { -5, 10, -1, 3, 20, 0, 8, -4, 15, 6 };
    execute_task_list(l1, 2, 10);

    return 0;
}
