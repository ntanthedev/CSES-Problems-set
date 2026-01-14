#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> h(n), s(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> s[i];

    vector<int> total(x + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = x; j >= h[i]; --j) {
            total[j] = max(total[j], s[i] + total[j - h[i]]);
        }
    }

    cout << total[x] << "\n";
}
