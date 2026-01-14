#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        cout << min(a, b) << ' ' << max(a, b) << '\n';
    }
}
