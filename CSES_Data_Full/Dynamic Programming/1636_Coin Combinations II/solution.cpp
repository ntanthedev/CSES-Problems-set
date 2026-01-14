#include <iostream>
#include <vector>
using namespace std;
const int M = 1000000007;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
    }

    vector<int> ways(x + 1);
    ways[0] = 1;
    for (int j = 0; j < n; ++j) {
        for (int i = c[j]; i <= x; ++i) {
            ways[i] = (ways[i - c[j]] + ways[i]) % M;
        }
    }

    cout << ways[x] << "\n";
}
