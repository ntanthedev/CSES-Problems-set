#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> amount(x + 1);
    amount[0] = 0;
    for (int i = 1; i <= x; ++i) {
        amount[i] = INF;
        for (int j = 0; j < n; ++j) {
            if (i - c[j] >= 0) {
                amount[i] = min(amount[i], amount[i - c[j]] + 1);
            }
        }
    }

    int answer = amount[x];
    if (answer == INF) answer = -1;
    cout << answer << "\n";
}
