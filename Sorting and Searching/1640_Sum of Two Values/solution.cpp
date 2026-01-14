#include <iostream>
#include <map>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if (m[x - a]) {
            cout << m[x - a] << " " << i << "\n";
            return 0;
        }
        m[a] = i;
    }
    cout << "IMPOSSIBLE\n";
}
