#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            sum ^= x;
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
