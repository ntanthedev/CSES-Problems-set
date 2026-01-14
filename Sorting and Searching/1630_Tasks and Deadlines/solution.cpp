#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> tasks;
    for (int i = 1; i <= n; i++) {
        int duration, deadline;
        cin >> duration >> deadline;
        tasks.emplace_back(duration, deadline);
    }
    sort(tasks.begin(), tasks.end());

    ll time = 0;
    ll reward = 0;
    for (auto [duration, deadline] : tasks) {
        time += duration;
        reward += deadline - time;
    }
    cout << reward << "\n";
}
