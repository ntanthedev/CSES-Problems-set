#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<ll> sums;
    sums.push_back(0);
    multiset<ll> order;

    ll sum = 0;
    ll answer = -1e18;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        sums.push_back(sum);

        if (i >= a) {
            order.insert(sums[i - a]);
            answer = max(answer, sum - *order.begin());
        }

        if (i >= b) {
            order.erase(order.find(sums[i - b]));
        }
    }

    cout << answer << "\n";
}
