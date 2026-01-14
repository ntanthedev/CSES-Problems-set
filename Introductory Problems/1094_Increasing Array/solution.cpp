#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    ll res = 0;
    for (int i = 2; i <= n; i++) {
        if (x[i] < x[i - 1]) {
            res += x[i - 1] - x[i];
            x[i] = x[i - 1];
        }
    }
    cout << res << "\n";
}
