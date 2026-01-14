#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<bool> seen(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int x;
        cin >> x;
        seen[x] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            cout << i << "\n";
        }
    }
}
