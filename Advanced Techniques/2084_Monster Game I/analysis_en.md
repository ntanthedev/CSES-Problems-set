# 2084 - Monster Game I

For each $i$, we will find the minimum possible time to kill the $i$th monster
and possibly some other monsters before it. Let us focus on the $i$th monster.
Assuming we have solved the minimum time for each previous monster, we have
$i-1$ offers of the form $(t\_j, f\_j)$, where $t\_j$ is the minimum possible time
it takes to kill the $j$th monster and $f\_j$ is the player's skill factor after
killing the $j$th monster.

For any offer $j < i$, it takes $s\_i\cdot f\_j$ more time to kill the $i$th
monster and thus $t = t\_j + s\_i \cdot f\_j$ time in total. Notice that the offers
can be thought of geometrically as lines $y = ax + b$ where the height of a line
at point $x$ corresponds to the total time it takes to kill a monster of
strength $x$.

We are interested in finding out the minimum possible time it takes to kill the
$i$th monster. In other words, the minimum height of a line at point $x=s\_i$.

![](6bdbfb9f8178d82c4e9c632f32f494b981c6d884a47e2260f532859b335c2b34)

Existing offers do not change depending on our position in the array, that is,
they do not depend on $i$. This means that if we are able to find an efficient
data structure for inserting and storing the lines, it may be used for
calculating the best time for each $i$.

![](52a65a8e853fb3b46db50e1a921a85bc5ce82892182f88a12c396998cb8b31d7)

Note the minimum line changes depending on $x$. In fact, the lines divide the
$x$-axis into ranges where a certain line is the lowest. As can be seen from the
picture, each line corresponds to at most one range, which means the $x$-axis
is divided into at most $n$ segments.

Let us analyze the situation a bit further. Recall from the task statement that
the slopes of the lines ($f\_i$'s) are decreasing and the points at which we are
querying the best line ($s\_i$'s) are increasing. The slopes of the minimum lines
are also in decreasing order. This means that each new offer will be the new
last minimum line. This allows us to maintain a simple array of lines and push
each new offer to the back of it.

Note that some lines may never have the minimum value. This is the case for the
fourth line in the picture. When adding a new line to the back of the array, we
need to check if it makes the previous line redundant. If that is the case, we
can simply pop the previous line from the array before adding the new one.

There is a simple way for checking whether the new line will make the previous
one redundant. It suffices to compare two intersection points. Let $x\_1$ be the
intersection of the last line and the one before that and $x\_2$ the intersection
point of the last line and the new one. The last line will become redundant if
$x\_1\ge x\_2$. This is because the last line has the minimum value on the range
$[x\_1, x\_2]$.

![](7f7105ef40e859ae11b940f615f6dad16e83a0d34b70494ccac6b8eff285476c)

To find the minimum line at position $x$, we may use binary search. However, as
the sequence of query points is increasing, it is also possible to just maintain
a pointer to the array of lines, which makes the amortized cost of querying
$O(1)$. In total, the solution has a time complexity of $O(n)$. The key idea of
maintaining the convex hull of linear functions is known as the *convex hull
trick*.

```cpp
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
```

## References

* [CP-Algorithms, *Convex hull trick*](https://cp-algorithms.com/geometry/convex_hull_trick.html)