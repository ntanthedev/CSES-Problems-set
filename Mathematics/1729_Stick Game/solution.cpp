#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> move(k);
    for (int i = 0; i < k; i++) {
        cin >> move[i];
    }

    string pos(n + 1, 'L');
    for (int i = 1; i <= n; i++) {
        for (auto m : move) {
            if (i - m >= 0 && pos[i - m] == 'L') {
                pos[i] = 'W';
            }
        }
    }
    cout << pos.substr(1) << "\n";
}
