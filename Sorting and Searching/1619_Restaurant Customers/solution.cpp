#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(a, 1);
        events.emplace_back(b, -1);
    }
    sort(events.begin(), events.end());

    int count = 0;
    int high = 0;
    for (auto [t, d] : events) {
        count += d;
        high = max(high, count);
    }
    cout << high << "\n";
}
