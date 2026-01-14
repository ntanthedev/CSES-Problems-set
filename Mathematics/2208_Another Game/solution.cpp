#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        bool win = false;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x % 2 == 1) win = true;
        }
        cout << (win ? "first" : "second") << "\n";
    }
}
