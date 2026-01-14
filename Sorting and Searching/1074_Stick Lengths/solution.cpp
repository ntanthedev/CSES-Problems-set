#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> lengths(n);
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
    }

    sort(lengths.begin(), lengths.end());
    int target = lengths[n / 2];

    ll cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(target - lengths[i]);
    }
    cout << cost << "\n";
}
