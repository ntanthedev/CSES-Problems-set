#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;

        if (a + b > n) {
            cout << "NO\n";
            continue;
        }

        if ((a == 0 || b == 0) && a + b != 0) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
        for (int i = 1; i <= b; i++) {
            cout << a + i << " ";
        }
        for (int i = 1; i <= a; i++) {
            cout << i << " ";
        }
        for (int i = a + b + 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
    }
}
