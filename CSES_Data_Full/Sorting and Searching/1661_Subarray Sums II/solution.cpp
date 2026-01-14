#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int n, x;
    cin >> n >> x;

    map<ll, int> sums;
    sums[0] = 1;

    ll sum = 0;
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum += a;
        count += sums[sum - x];
        sums[sum]++;
    }

    cout << count << "\n";
}
