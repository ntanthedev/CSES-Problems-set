#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    int n;
    // If p[i] < 0, i is a root node with a tree size of -p[i].
    // Otherwise, p[i] represents the parent of i.
    vector<int> p;
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
        p[b] += p[a];
        p[a] = b;
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    UnionFind graph(n);
    vector<pair<int, int>> edges(m);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        a--;
        b--;
        graph.merge(a, b);
    }

    vector<int> qa(q), qb(q), ql(q), qr(q);
    for (int i = 0; i < q; ++i) {
        int &a = qa[i], &b = qb[i];
        cin >> a >> b;
        a--;
        b--;
        ql[i] = 0;
        qr[i] = m;
    }

    int log2 = __lg(m + 1);

    for (int t = 0; t < log2 + 1; ++t) {
        vector<vector<int>> queries(m + 1);
        for (int i = 0; i < q; ++i) {
            if (ql[i] < qr[i]) {
                queries[(ql[i] + qr[i]) / 2].push_back(i);
            }
        }
        UnionFind uf(n);
        for (int i = 0; i < m; ++i) {
            for (int qi : queries[i]) {
                if (uf.root(qa[qi]) == uf.root(qb[qi])) {
                    qr[qi] = i;
                } else {
                    ql[qi] = i + 1;
                }
            }
            uf.merge(edges[i].first, edges[i].second);
        }
    }

    for (int i = 0; i < q; ++i) {
        if (graph.root(qa[i]) != graph.root(qb[i])) {
            cout << -1 << '\n';
        } else {
            cout << ql[i] << '\n';
        }
    }
}
