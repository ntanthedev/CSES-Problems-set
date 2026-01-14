#include <iostream>
#include <vector>
using namespace std;

const int N = 20;
pair<int, int> best[1 << N];

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> w(n);
    for (int i = 0; i < n; ++i) cin >> w[i];

    best[0] = {1, 0};
    for (int s = 1; s < (1 << n); ++s) {
        best[s] = {n + 1, 0};

        for (int p = 0; p < n; ++p) {
            if (s & (1 << p)) {
                auto [r, l] = best[s ^ (1 << p)];
                pair<int, int> added;
                if (l + w[p] <= x) {
                    added = {r, l + w[p]};
                } else {
                    added = {r + 1, w[p]};
                }
                best[s] = min(best[s], added);
            }
        }
    }

    cout << best[(1 << n) - 1].first << endl;
}
