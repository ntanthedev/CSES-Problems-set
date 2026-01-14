#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> heights;
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        heights.emplace_back(h, i);
    }
    sort(heights.rbegin(), heights.rend());

    map<int, int> counts;
    counts[0] = 0;
    counts[n + 1] = 0;

    int prev_height = 0;
    vector<pair<int, int>> updates;
    int result = 0;

    for (auto [height, pos] : heights) {
        if (height != prev_height) {
            for (auto [pos, count] : updates) {
                counts[pos] = count;
            }
            updates.clear();
            prev_height = height;
        }

        auto it = counts.upper_bound(pos);
        int next_pos = it->first;
        it--;
        int prev_pos = it->first;

        int new_count = max(counts[prev_pos], counts[next_pos]) + 1;
        updates.emplace_back(pos, new_count);
        result = max(result, new_count);
    }

    cout << result << "\n";
}
