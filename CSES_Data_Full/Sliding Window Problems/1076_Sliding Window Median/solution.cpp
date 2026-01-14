#include <iostream>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    indexed_set<pair<int, int>> s;

    for (int i = 0; i < n; i++) {
        s.insert({x[i], i});
        if (i >= k) {
            s.erase({x[i - k], i - k});
        }
        if (i >= k - 1) {
            int median = s.find_by_order((k - 1) / 2)->first;
            cout << median << " ";
        }
    }
    cout << "\n";
}
