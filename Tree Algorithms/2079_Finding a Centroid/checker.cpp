/*

* Problem:      2079 Finding a Centroid
* Input read:   n; n-1 tree edges
* Validity:     Output one node c in [1,n] such that every component after removing c
* ```
            has size at most floor(n/2)
* Optimality:   Any valid centroid is accepted
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<vector<int>> g(n + 1);
for (int i = 0; i < n - 1; i++) {
    int a = inf.readInt();
    int b = inf.readInt();

    g[a].push_back(b);
    g[b].push_back(a);
}

int c = ouf.readInt(1, n, "centroid");

vector<int> parent(n + 1, 0), order;
order.reserve(n);

vector<int> st;
st.push_back(c);
parent[c] = -1;

while (!st.empty()) {
    int u = st.back();
    st.pop_back();
    order.push_back(u);

    for (int v : g[u]) {
        if (v == parent[u]) continue;

        parent[v] = u;
        st.push_back(v);
    }
}

if ((int)order.size() != n) {
    quitf(_fail, "input graph is not connected");
}

vector<int> sub(n + 1, 1);

for (int i = n - 1; i >= 0; i--) {
    int u = order[i];

    for (int v : g[u]) {
        if (parent[v] == u) {
            sub[u] += sub[v];
        }
    }
}

int maxComponent = 0;
for (int v : g[c]) {
    if (parent[v] == c) {
        maxComponent = max(maxComponent, sub[v]);
    }
}

if (maxComponent > n / 2) {
    quitf(_wa, "node %d is not a centroid: a component has size %d, greater than %d",
          c, maxComponent, n / 2);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid centroid %d", c);

}
