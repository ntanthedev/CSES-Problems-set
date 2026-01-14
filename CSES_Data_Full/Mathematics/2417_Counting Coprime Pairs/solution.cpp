#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1000000;

int main() {
    vector<int> total(N + 1);

    int n;
    cin >> n;
    ll answer = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        vector<int> factors;
        for (int f = 2; f * f <= x; f++) {
            if (x % f == 0) {
                factors.push_back(f);
                while (x % f == 0) x /= f;
            }
        }
        if (x != 1) factors.push_back(x);

        int k = factors.size();
        for (int b = 1; b < (1 << k); b++) {
            int prod = 1;
            for (int i = 0; i < k; i++) {
                if (b & (1 << i)) prod *= factors[i];
            }

            int add = total[prod];
            if (__builtin_parity(b) == 0) add = -add;
            answer += add;
            total[prod]++;
        }
    }

    cout << (n * ll(n - 1) / 2) - answer << "\n";
}
