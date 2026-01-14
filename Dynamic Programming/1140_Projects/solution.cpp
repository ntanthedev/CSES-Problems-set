#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Event {
    int time, project;
    bool is_end;
    bool operator<(Event other) const {
        if (time == other.time) return is_end < other.is_end;
        return time < other.time;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<ll> money(n);
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b >> p[i];
        events.push_back({a, i, false});
        events.push_back({b, i, true});
        money[i] = 0;
    }

    sort(events.begin(), events.end());

    ll result = 0;
    for (auto [time, project, is_end] : events) {
        if (is_end) {
            result = max(result, money[project]);
        } else {
            money[project] = result + p[project];
        }
    }

    cout << result << endl;
}
