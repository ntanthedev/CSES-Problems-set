#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    sort(values.begin(), values.end());

    ll largest = 0;
    for (int i = 0; i < n; i++) {
        if (values[i] > largest + 1) {
            break;
        }
        largest += values[i];
    }
    cout << largest + 1 << "\n";
}
