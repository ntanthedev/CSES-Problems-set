#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    ll diff = 1e9;
    for (int b = 0; b < (1 << n); b++) {
        ll sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            if (b & (1 << i)) {
                sum1 += p[i];
            } else {
                sum2 += p[i];
            }
        }
        diff = min(diff, abs(sum1 - sum2));
    }

    cout << diff << "\n";
}
