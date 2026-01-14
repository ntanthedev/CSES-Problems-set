#include <iostream>
using namespace std;

const int N = 200001;
const int LOG_X = 30;
const int NODES = N * LOG_X;

int c[NODES][2], nodes = 1;

void add(int x) {
    int n = 0;
    for (int shift = LOG_X - 1; shift >= 0; --shift) {
        int bit = x >> shift & 1;
        if (!c[n][bit]) c[n][bit] = nodes++;
        n = c[n][bit];
    }
}

int query(int x) {
    int n = 0, ret = 0;
    for (int shift = LOG_X - 1; shift >= 0; --shift) {
        int bit = ~x >> shift & 1;
        if (!c[n][bit]) {
            n = c[n][!bit];
        } else {
            ret += 1 << shift;
            n = c[n][bit];
        }
    }
    return ret;
}

int x[N];

int main() {
    int n;
    cin >> n;

    int ans = 0, sum = 0;
    add(0);

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum ^= x[i];
        ans = max(ans, query(sum));
        add(sum);
    }

    cout << ans << '\n';
}
