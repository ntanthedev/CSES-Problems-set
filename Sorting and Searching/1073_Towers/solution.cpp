#include <iostream>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<int> towers;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        auto it = towers.upper_bound(x);
        if (it == towers.end()) {
            towers.insert(x);
        } else {
            towers.erase(it);
            towers.insert(x);
        }
    }
    cout << towers.size() << "\n";
}
