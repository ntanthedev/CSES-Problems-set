#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> movies;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        movies.emplace_back(b, a);
    }
    sort(movies.begin(), movies.end());

    int count = 0;
    int end = 0;
    for (auto [b, a] : movies) {
        if (a >= end) {
            end = b;
            count++;
        }
    }
    cout << count << "\n";
}
