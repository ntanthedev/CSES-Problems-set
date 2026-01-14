#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(b, a);
    }
    sort(events.begin(), events.end());

    multiset<int> times;
    for (int i = 1; i <= k; i++) {
        times.insert(0);
    }

    int answer = 0;
    for (auto [b, a] : events) {
        auto it = times.upper_bound(a);
        if (it == times.begin()) continue;
        answer++;
        it--;
        times.erase(it);
        times.insert(b);
    }

    cout << answer << "\n";
}
