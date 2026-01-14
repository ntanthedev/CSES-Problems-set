#include <iostream>
#include <map>
#include <set>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;

    map<int, int> prev;
    set<pair<int, int>> rank;
    ll count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        rank.erase({prev[x], x});
        rank.insert({i, x});
        prev[x] = i;

        if (rank.size() > k + 1) {
            rank.erase(rank.begin());
        }

        if (rank.size() <= k) {
            count += i;
        } else {
            count += i - rank.begin()->first;
        }
    }

    cout << count << "\n";
}
