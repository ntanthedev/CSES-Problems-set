#include <iostream>
#include <vector>
using namespace std;
const int N = 1e7;

int main() {
    int t;
    cin >> t;

    vector<bool> can(N + 1);
    vector<int> first(N + 1), second(N + 1);
    for (int a = 0; a * a <= N; a++) {
        for (int b = 0; a * a + b * b <= N; b++) {
            int x = a * a + b * b;
            can[x] = true;
            first[x] = a;
            second[x] = b;
        }
    }

    while (t--) {
        int n;
        cin >> n;
        for (int x = 0; x <= n; x++) {
            if (can[x] && can[n - x]) {
                cout << first[x] << " " << second[x] << " ";
                cout << first[n - x] << " " << second[n - x] << "\n";
                break;
            }
        }
    }
}
