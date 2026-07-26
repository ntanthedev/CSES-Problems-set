/*

* Problem:      1685 New Flight Routes
* Input read:   n, m; m directed flights
* Validity:     Output k equal to the optimum from ans, then k directed new flights
* ```
            with endpoints in [1,n]; after adding them, the graph must be strongly connected
* Optimality:   k must equal the minimum number of new flights from ans
* Complexity:   O(n + m + k) time, O(n + m + k) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static vector<int> finish_order_iterative(const vector<vector<int>>& g) {
int n = (int)g.size() - 1;
vector<char> vis(n + 1, 0);
vector<int> order;
order.reserve(n);

for (int start = 1; start <= n; start++) {
    if (vis[start]) continue;

    vector<pair<int, int>> st;
    st.push_back({start, 0});
    vis[start] = 1;

    while (!st.empty()) {
        int u = st.back().first;
        int& idx = st.back().second;

        if (idx < (int)g[u].size()) {
            int v = g[u][idx++];
            if (!vis[v]) {
                vis[v] = 1;
                st.push_back({v, 0});
            }
        } else {
            order.push_back(u);
            st.pop_back();
        }
    }
}

return order;

}

static int count_scc(const vector<vector<int>>& g, const vector<vector<int>>& rg) {
int n = (int)g.size() - 1;

vector<int> order = finish_order_iterative(g);
vector<char> assigned(n + 1, 0);

int comps = 0;

for (int it = n - 1; it >= 0; it--) {
    int start = order[it];
    if (assigned[start]) continue;

    comps++;

    vector<int> st;
    st.push_back(start);
    assigned[start] = 1;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (int v : rg[u]) {
            if (!assigned[v]) {
                assigned[v] = 1;
                st.push_back(v);
            }
        }
    }
}

return comps;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

vector<vector<int>> g(n + 1), rg(n + 1);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    g[a].push_back(b);
    rg[b].push_back(a);
}

int optimal = ans.readInt();

int k = ouf.readInt(0, n, "number of new flights");
if (k != optimal) {
    quitf(_wa, "contestant printed %d new flights, but optimum is %d", k, optimal);
}

for (int i = 1; i <= k; i++) {
    int a = ouf.readInt(1, n, format("new_flight[%d].from", i).c_str());
    int b = ouf.readInt(1, n, format("new_flight[%d].to", i).c_str());

    g[a].push_back(b);
    rg[b].push_back(a);
}

int comps = count_scc(g, rg);
if (comps != 1) {
    quitf(_wa, "after adding the flights, the graph still has %d strongly connected components",
          comps);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid minimum solution with %d new flights", k);

}
