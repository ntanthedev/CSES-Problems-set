#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9;

int main() {
    int n;
    cin >> n;

    vector<int> steps(n + 1);
    steps[0] = 0;
    for (int i = 1; i <= n; ++i) {
        steps[i] = INF;
        int number = i;
        while (number) {
            int digit = number % 10;
            steps[i] = min(steps[i], steps[i - digit] + 1);
            number /= 10;
        }
    }

    cout << steps[n] << "\n";
}
