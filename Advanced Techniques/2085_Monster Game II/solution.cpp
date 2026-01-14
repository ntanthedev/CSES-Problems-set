#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Line {
    ll a, b;  // Represents the line y = ax + b
    // Returns the height of the line at x.
    ll operator()(ll x) const { return a * x + b; }
    bool operator<(Line oth) const {
        return a != oth.a ? a > oth.a : b < oth.b;
    }
    ll intersect(Line oth) {
        ll num = oth.b - b, dem = a - oth.a;
        return num / dem - ((num ^ dem) < 0 && num % dem);
    }
};

struct Hull {
    // Stores all lines regardless of whether they are part of the hull or not.
    vector<Line> all;
    // Stores the convex hull lines and the intersection points between
    // subsequent lines.
    vector<pair<ll, Line>> hull;
    Hull(Line x) : all{x}, hull{{-INF, x}} {}
    // Constructs a new hull out of hulls a and b.
    Hull(const Hull &a, const Hull &b) {
        all.resize(a.size() + b.size());
        // Note that because the lines of a and b are already sorted, we are
        // able to merge them in O(N) time without needing to sort the array.
        merge(a.all.begin(), a.all.end(), b.all.begin(), b.all.end(),
              all.begin());
        hull.emplace_back(-INF, all[0]);
        for (int i = 1; i < (int)all.size(); ++i) {
            auto l = all[i];
            if (hull.back().second.a == l.a) continue;
            while (hull.size() >= 2) {
                auto al = hull[hull.size() - 2].second;
                auto bl = hull[hull.size() - 1].second;
                if (bl.intersect(l) <= al.intersect(bl)) {
                    hull.pop_back();
                } else {
                    break;
                }
            }
            hull.emplace_back(hull.back().second.intersect(l), l);
        }
    }
    // Returns the lowest line at point x.
    ll query(ll x) const {
        auto p = pair{x, Line{INF, INF}};
        auto it = prev(lower_bound(hull.begin(), hull.end(), p));
        return it->second(x);
    }
    size_t size() const { return all.size(); }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    vector<Hull> hulls;
    hulls.emplace_back(Line{x, 0});

    auto best_line = [&](ll x) {
        ll r = INF;
        for (auto &h : hulls) r = min(r, h.query(x));
        return r;
    };

    for (int i = 0; i < n - 1; ++i) {
        ll b = best_line(s[i]);
        hulls.emplace_back(Line{f[i], b});
        while (hulls.size() > 1) {
            auto &a = hulls[hulls.size() - 2];
            auto &b = hulls[hulls.size() - 1];
            if (a.size() == b.size()) {
                a = Hull(a, b);
                hulls.pop_back();
            } else {
                break;
            }
        }
    }

    cout << best_line(s[n - 1]) << '\n';
}
