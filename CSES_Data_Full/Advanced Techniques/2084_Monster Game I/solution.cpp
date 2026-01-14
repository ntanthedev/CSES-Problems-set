#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Line {
    ll a, b;  // Represents the line y = ax + b
    // Returns the height of the line at x.
    ll operator()(ll x) { return a * x + b; }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    vector<Line> lines;
    lines.push_back({x, 0});

    int pos = 0;  // Stores the index of the current lowest line.

    // Finds the height of the lowest line at position x.
    // Assumes that the sequence of x's is increasing.
    auto get_best = [&](ll x) {
        while (pos + 1 < lines.size() && lines[pos + 1](x) < lines[pos](x)) {
            pos++;
        }
        return lines[pos](x);
    };

    for (int i = 0; i < n - 1; ++i) {
        ll b = get_best(s[i]);
        Line l = {f[i], b};
        while (lines.size() > 1) {
            auto a = lines[lines.size() - 2];
            auto b = lines[lines.size() - 1];
            // Compare x1 and x2.
            //
            //      b.b - a.b          l.b - a.b
            // x1 = ---------     x2 = ---------
            //      a.a - b.a          a.a - l.a
            if ((l.b - a.b) * (a.a - b.a) <= (b.b - a.b) * (a.a - l.a)) {
                lines.pop_back();
            } else {
                break;
            }
        }
        lines.push_back(l);
    }

    cout << get_best(s[n - 1]) << '\n';
}
