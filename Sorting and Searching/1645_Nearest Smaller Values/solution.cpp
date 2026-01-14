#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> stack;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (!stack.empty() && stack.back().first >= x) {
            stack.pop_back();
        }
        if (!stack.empty()) {
            cout << stack.back().second << " ";
        } else {
            cout << 0 << " ";
        }
        stack.emplace_back(x, i);
    }
    cout << "\n";
}
