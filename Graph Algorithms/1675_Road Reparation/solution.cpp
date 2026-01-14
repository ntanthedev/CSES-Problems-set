#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;
using ll = long long;

const int N = 100001;

int sz[N];
int link[N];

int find(int x) {
    if (link[x] == x) {
        return x;
    }
    return link[x] = find(link[x]);
}

bool same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (sz[x] < sz[y]) {
        swap(x, y);
    }
    sz[x] += sz[y];
    link[y] = x;
}

int main() {
    int n, m;
    cin >> n >> m;

    fill(sz, sz + n + 1, 1);
    iota(link, link + n + 1, 0);

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
    }

    sort(edges.begin(), edges.end(),
         [](auto x, auto y) { return get<2>(x) < get<2>(y); });

    ll cost = 0;
    for (auto [a, b, c] : edges) {
        if (!same(a, b)) {
            unite(a, b);
            cost += c;
        }
    }

    if (sz[find(1)] != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << cost << '\n';
}
