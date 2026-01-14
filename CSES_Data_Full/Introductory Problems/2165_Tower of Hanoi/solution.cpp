#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> moves;

void move(int n, int a, int b, int c) {
    if (n == 1) {
        moves.emplace_back(a, b);
    } else {
        move(n - 1, a, c, b);
        move(1, a, b, c);
        move(n - 1, c, b, a);
    }
}

int main() {
    int n;
    cin >> n;
    move(n, 1, 3, 2);
    cout << moves.size() << "\n";
    for (auto [a, b] : moves) {
        cout << a << " " << b << "\n";
    }
}
