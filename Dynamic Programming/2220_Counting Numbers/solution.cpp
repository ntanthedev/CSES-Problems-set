#include <array>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

string s;
map<array<int, 4>, ll> lookup;

ll recurse(int i, int prev, bool equal, bool empty) {
    if (i == (int)s.size()) return 1;

    array<int, 4> params{i, prev, equal, empty};
    if (lookup.count(params)) return lookup[params];

    ll result = 0;
    for (int d = 0; d < 10; ++d) {
        if (equal && d > s[i] - '0') break;
        if (!empty && d == prev) continue;
        result += recurse(i + 1, d, equal && d == s[i] - '0', empty && d == 0);
    }

    lookup[params] = result;
    return result;
}

ll count(ll x) {
    if (x < 0) return 0;
    s = to_string(x);
    lookup.clear();
    return recurse(0, 0, true, true);
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << count(b) - count(a - 1) << endl;
}
