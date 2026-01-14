#include <iostream>
using namespace std;
const int N = 500 * 501 / 4;
const int M = 1000000007;

int sets[N + 1];

int main() {
    int n;
    cin >> n;

    int total = n * (n + 1) / 2;
    if (total % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }
    int half = total / 2;

    sets[0] = 1;
    for (int x = 1; x < n; ++x) {
        for (int s = half; s - x >= 0; --s) {
            sets[s] = (sets[s] + sets[s - x]) % M;
        }
    }

    cout << sets[half] << endl;
}
