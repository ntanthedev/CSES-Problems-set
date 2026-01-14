#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    auto f = [&](int i) {
        return pow(1.0 * i / k, n);
    };

    double answer = 0;
    for (int i = k; i >= 1; i--) {
        answer += i * (f(i) - f(i - 1));
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
