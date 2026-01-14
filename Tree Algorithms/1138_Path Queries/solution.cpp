#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct FenwickTree {
    int n;
    vector<ll> tree;

    FenwickTree(int n) : n(n), tree(n + 1) {}

    void add(int k, int d) {
        while (k <= n) {
            tree[k] += d;
            k += k & -k;
        }
    }

    ll query(int k) {
        ll s = 0;
        while (k > 0) {
            s += tree[k];
            k -= k & -k;
        }
        return s;
    }
};

const int N = 200001;
vector<int> g[N];
int order_in[N], order_out[N], order_index = 1;

void dfs(int node, int parent) {
    order_in[node] = order_index++;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
    }
    order_out[node] = order_index;
}

int value[N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    FenwickTree tree(n);

    for (int i = 1; i <= n; ++i) {
        tree.add(order_in[i], value[i]);
        tree.add(order_out[i], -value[i]);
    }

    for (int qi = 1; qi <= q; ++qi) {
        int t, s;
        cin >> t >> s;
        if (t == 1) {
            int x;
            cin >> x;
            tree.add(order_in[s], -value[s]);
            tree.add(order_out[s], value[s]);
            value[s] = x;
            tree.add(order_in[s], value[s]);
            tree.add(order_out[s], -value[s]);
        } else {
            cout << tree.query(order_in[s]) << '\n';
        }
    }
}
