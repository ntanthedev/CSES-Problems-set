#include <iostream>
using namespace std;
const int X = 100000;

bool possible[X + 1];

int main() {
    int n;
    cin >> n;

    possible[0] = true;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        for (int s = X; s >= x; --s) {
            possible[s] |= possible[s - x];
        }
    }

    int k = 0;
    for (int s = 1; s <= X; ++s) {
        k += possible[s];
    }
    cout << k << "\n";
    for (int s = 1; s <= X; ++s) {
        if (possible[s]) cout << s << " ";
    }
    cout << "\n";
}
