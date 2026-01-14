#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Union find structure with rollback functionality.
struct UnionFind {
    // Stores the number of disjoint trees.
    int n;
    // If p[i] < 0, i is a root node with a tree size of -p[i].
    // Otherwise, p[i] represents the parent of i.
    vector<int> p;
    vector<pair<int *, int>> changes;
    UnionFind(int n) : n(n), p(n, -1) {}
    int root(int s) {
        while (p[s] >= 0) {
            s = p[s];
        }
        return s;
    }
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (p[a] < p[b]) swap(a, b);
        changes.emplace_back(&p[a], p[a]);
        changes.emplace_back(&p[b], p[b]);
        changes.emplace_back(&n, n);
        n--;
        p[b] += p[a];
        p[a] = b;
    }
    void undo(int cnt) {
        while (cnt--) {
            auto [a, b] = changes.back();
            changes.pop_back();
            *a = b;
        }
    }
};

using Event = tuple<int, int, int, int>;

const int N = 100001;
int ans[N];
UnionFind uf(0);

void answer(int l, int r, vector<Event> edges) {
    int old_size = uf.changes.size();
    int mid = (l + r) / 2;
    vector<Event> left, right;
    for (auto &e : edges) {
        auto [t0, t1, a, b] = e;
        if (t0 <= l && r <= t1) {
            uf.merge(a, b);
        } else {
            if (t0 < mid) {
                left.emplace_back(e);
            }
            if (mid < t1) {
                right.emplace_back(e);
            }
        }
    }
    if (r - l == 1) {
        ans[l] = uf.n;
    } else {
        answer(l, mid, left);
        answer(mid, r, right);
    }
    uf.undo(uf.changes.size() - old_size);
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    map<pair<int, int>, int> edge_time;
    vector<Event> edges;

    for (int i = 0; i < m + k; ++i) {
        int _, a, b;
        if (i >= m) cin >> _;
        cin >> a >> b;
        a--;
        b--;
        if (b < a) swap(a, b);
        int t = max(0, i - (m - 1));
        if (auto it = edge_time.find({a, b}); it != edge_time.end()) {
            edges.emplace_back(it->second, t, a, b);
            edge_time.erase(it);
        } else {
            edge_time.insert(it, {{a, b}, t});
        }
    }

    for (auto [e, t] : edge_time) {
        auto [a, b] = e;
        edges.emplace_back(t, k + 1, a, b);
    }

    uf = UnionFind(n);
    answer(0, k + 1, edges);

    for (int i = 0; i < k + 1; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
