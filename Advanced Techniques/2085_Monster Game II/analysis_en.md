# 2085 - Monster Game II

Three separate approaches to this problem are presented below. We are trying
to solve, for each $i$, the minimum time it takes to kill the $i$th monster and
possibly some others before it. The key idea in all of the solutions is that
these minimum times $t\_1, t\_2, \dots t\_n$ form offers of the form $(t\_i, f\_i)$,
where $t\_i$ is the minimum time it takes to kill the $i$th monster and $f\_i$ is
the player's strength after killing the monster. These offers remain the same
for all $j>i$.

With this observation, the task turns into one where we have to find a data
structure for storing the offers and querying the lowest total time for a
monster of strength $s\_i$. The total time for killing monster $i$ by utilizing
offer $j$ is $t\_j+f\_j\cdot s\_i$. The offers can be thought of geometrically as
lines and the different approaches to this problem are known collectively as
the *convex hull trick*.

## Solution 1: Ordinary Convex Hull Trick & Bentley-Saxe Transformation

The simplest possible data structure for storing the convex hull is an array.
However, an array does not allow efficient insertions to the middle of it. Thus,
by itself, a simple array would be too slow. Fortunately, there is a way to
speed up this solution. It is known as the *Bentley-Saxe transformation*.

The Bentley-Saxe transformation allows us to make insertions to static data
structures, i.e. ones that do not support insertions, turning them into dynamic
ones. The key idea is to maintain $O(\log N)$ static data structures and to
merge two of them when they are of equal size. Merging two hulls means taking
their lines and constructing a completely new hull from the ground up. The
process goes like this:

* Maintain a stack of static hulls.
* When adding a new line, make a hull of only the new line, and push it onto
  the stack.
* Whenever the two latest data structures in the back of the stack are of equal
  size, merge them into a new hull of double the size.

This process ensures that, at all times, we have at most $O(\log N)$ data
structures to query from and that each line is merged at most $O(\log N)$ times.
The total time complexity of the construction is $O(N \log N)$ as each line
contributes $O(1)$ work to the construction of each of the hulls it is part of.
Querying takes $O(\log^2 N)$ time as there are $O(\log N)$ hulls and binary
search needs to be done in each of them to find the best line.

## References

* [CP-Algorithms, *Convex Hull Trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)
* [J. L. Bentley,
  J. B. Saxe,
  Decomposable searching problems I. Static-to-dynamic transformation,
  Journal of Algorithms,
  Volume 1,
  Issue 4,
  1980](https://www.sciencedirect.com/science/article/pii/0196677480900152)

```cpp
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
```

## Solution 2: Set Structure

Another approach is to store the lines in a set structure. The set maintains the
order of the lines and if we store the intersection points of subsequent lines,
we are again able to find the minimum line at a point using binary search.

Inserting a line has an amortized cost of $O(\log N)$ as there may be multiple
deletions following an insertion but each line can be deleted only once.
Querying the minimum line at a point takes $O(\log N)$ time. The downside of
this approach is that the set structure is cumbersome to implement as the hull
and intersection points have to be maintained and updated with each insertion.

## References

* [KACTL, ICPC Team Reference Document, LineContainer.h](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h)
* [CP-Algorithms, *Convex hull trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)

```cpp
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Line {
    ll a, b;  // Represents the line y = ax + b
    ll p;  // The x-coordinate at which this line intersects the previous one.
    // Returns the height of the line at x.
    ll operator()(ll x) const { return a * x + b; }
    bool operator<(Line oth) const { return a > oth.a; }
    bool operator<(ll x) const { return p < x; }
    ll intersect(Line oth) const {
        ll num = oth.b - b, dem = a - oth.a;
        return num / dem - ((num ^ dem) < 0 && num % dem);
    }
};

struct Hull {
    set<Line, less<>> hull;
    using Iter = set<Line, less<>>::iterator;
    // Recalculates the intersection point of the line at `it`.
    void fix(Iter it) {
        Line l = *it;
        it = hull.erase(it);
        if (it != end(hull)) {
            l.p = l.intersect(*it);
        } else {
            l.p = INF;
        }
        hull.insert(it, l);
    }
    // Check whether the line at `it` is useless.
    // A line is said to be useless if it never has the minimum value.
    bool check(Iter it) {
        if (it != begin(hull) && next(it) != end(hull)) {
            auto a = *prev(it);
            auto b = *it;
            auto c = *next(it);
            return __int128(a.b - c.b) * (b.a - a.a) <=
                   __int128(c.a - a.a) * (a.b - b.b);
        }
        return false;
    }
    // Insert line l into the hull.
    void insert(Line l) {
        auto it = hull.lower_bound(l);
        if (it != end(hull) && it->a == l.a) {
            if (l.b >= it->b) return;
            it = hull.erase(it);
        }
        it = hull.insert(it, l);
        if (check(it)) {
            hull.erase(it);
        } else {
            while (it != begin(hull) && check(prev(it))) {
                hull.erase(prev(it));
            }
            while (next(it) != end(hull) && check(next(it))) {
                hull.erase(next(it));
            }
            if (it != begin(hull)) fix(prev(it));
            if (next(it) != end(hull)) fix(next(it));
            fix(it);
        }
    }
    // Returns the lowest line at point x.
    ll query(ll x) const {
        // Note that we have implemented two separate comparator functions,
        // one for comparing lines with coordinates and another for comparing
        // with other lines.
        // When we compare a line with a coordinate, we are actually comparing
        // the start of the line's active range with the coordinate.
        Line l = *hull.lower_bound(x);
        return l(x);
    }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    Hull h;
    h.insert({x, 0});

    for (int i = 0; i < n - 1; ++i) {
        ll b = h.query(s[i]);
        h.insert({f[i], b});
    }

    cout << h.query(s[n - 1]) << '\n';
}
```

## Solution 3: Li Chao Tree

The last approach presented here is known as the *Li Chao tree*. It is a
variation on segment trees which allows us to store lines and query the minimum
line at a certain point. The only downside of the Li Chao tree approach is that
it requires us to know the query points beforehand.

## References

* [CP-Algorithms, *Li Chao Tree*](https://cp-algorithms.com/geometry/convex_hull_trick.html#toc-tgt-1)

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = numeric_limits<ll>::max();

struct Line {
    ll a, b;  // Represents the line y = ax + b
    // Returns the height of the line at x.
    ll operator()(ll x) const { return a * x + b; }
};

struct LiChao {
    int n;
    vector<Line> p;
    vector<ll> xs;

    // Constructs a Li Chao tree which supports the insertion of any line and
    // queries in all positions included in the array x.
    LiChao(vector<int> x) {
        n = 1;
        while (n <= x.size()) n *= 2;
        p.assign(n * 2, Line{0, INF});
        sort(x.begin(), x.end());
        while (x.size() < n) x.push_back(x.back());
        xs.assign(n * 2, 0);
        for (int i = 0; i < n; ++i) xs[i + n] = x[i];
        for (int i = n - 1; i > 0; --i) {
            xs[i] = xs[i * 2];
        }
    }

    // Inserts line x into the tree.
    void insert(Line x) {
        int s = 1;
        while (s < n) {
            ll p1 = xs[s * 2], p2 = xs[s * 2 + 1];
            bool c1 = x(p1) < p[s](p1);
            bool c2 = x(p2) < p[s](p2);
            if (c2) swap(x, p[s]);
            s = s * 2 + (c1 == c2);
        }
        if (x(xs[s]) < p[s](xs[s])) {
            p[s] = x;
        }
    }
    // Returns the lowest line at point x.
    // Note that x has to be included in the vector of points provided earlier.
    ll query(ll x) {
        int i = lower_bound(xs.begin() + n, xs.end(), x) - xs.begin();
        ll r = INF;
        while (i > 0) {
            r = min(r, p[i](x));
            i /= 2;
        }
        return r;
    }
};

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    LiChao l(s);
    l.insert({x, 0});

    for (int i = 0; i < n - 1; ++i) {
        ll b = l.query(s[i]);
        l.insert({f[i], b});
    }

    cout << l.query(s[n - 1]) << '\n';
}
```