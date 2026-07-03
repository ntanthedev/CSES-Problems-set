/*

* Problem:      1666 Building Roads
* Input read:   n, m; m undirected roads
* Validity:     Output k new roads with endpoints in [1,n], no self-loops; after adding
* ```
            them, all cities must be connected
* Optimality:   k must equal the minimum number of roads from ans
* Complexity:   O((n + m) alpha(n)) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

struct DSU {
vector<int> p, sz;

explicit DSU(int n) : p(n + 1), sz(n + 1, 1) {
    iota(p.begin(), p.end(), 0);
}

int find(int x) {
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
}

};

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

DSU dsu(n);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    dsu.unite(a, b);
}

int optimal = ans.readInt();

int k = ouf.readInt(0, n - 1, "number of new roads");
if (k != optimal) {
    quitf(_wa, "contestant printed %d new roads, but optimum is %d", k, optimal);
}

for (int i = 1; i <= k; i++) {
    int a = ouf.readInt(1, n, format("road[%d].a", i).c_str());
    int b = ouf.readInt(1, n, format("road[%d].b", i).c_str());

    if (a == b) {
        quitf(_wa, "road %d is a self-loop at city %d", i, a);
    }

    dsu.unite(a, b);
}

int root = dsu.find(1);
for (int city = 2; city <= n; city++) {
    if (dsu.find(city) != root) {
        quitf(_wa, "city %d is still disconnected after adding the roads", city);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid set of %d roads connects all cities", k);

}
