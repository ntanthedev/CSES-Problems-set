#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    double answer = 0;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int x_a = 1; x_a <= r[a]; x_a++) {
                for (int x_b = 1; x_b <= min(x_a - 1, r[b]); x_b++) {
                    answer += 1.0 / (r[a] * r[b]);
                }
            }
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
