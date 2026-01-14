#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000001;

ll towers[N][2];

int main() {
    towers[1][1] = 1;
    towers[1][0] = 1;

    for (int i = 2; i < N; ++i) {
        towers[i][1] = (4 * towers[i - 1][1] + towers[i - 1][0]) % M;
        towers[i][0] = (towers[i - 1][1] + 2 * towers[i - 1][0]) % M;
    }

    int t;
    cin >> t;
    for (int ti = 0; ti < t; ++ti) {
        int n;
        cin >> n;
        cout << (towers[n][0] + towers[n][1]) % M << "\n";
    }
}
