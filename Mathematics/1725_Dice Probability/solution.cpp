#include <iostream>
using namespace std;

const int N = 100;
double p[N + 1][6 * N + 1];

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    p[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i; j <= 6 * i; j++) {
            for (int k = 1; k <= 6; k++) {
                p[i + 1][j + k] += p[i][j] / 6;
            }
        }
    }

    double answer = 0;
    for (int i = a; i <= b; i++) {
        answer += p[n][i];
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
