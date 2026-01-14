#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> sums(n);
    sums[0] = 1;

    ll sum = 0;
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum += a;
        sum = (sum % n + n) % n;
        count += sums[sum];
        sums[sum]++;
    }

    cout << count << "\n";
}
