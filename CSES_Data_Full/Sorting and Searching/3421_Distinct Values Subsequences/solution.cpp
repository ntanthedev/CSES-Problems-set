#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    map<int, int> counts;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        counts[x]++;
    }

    ll answer = 1;
    for (auto [value, count] : counts) {
        answer *= (count + 1);
        answer %= M;
    }
    answer = (answer - 1 + M) % M;
    cout << answer << "\n";
}
