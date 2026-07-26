/*

* Problem:      1683 Planets and Kingdoms
* Input read:   n, m; m directed teleporters
* Validity:     Output k equal to jury's SCC count, then n labels in [1,k]; labels must
* ```
            partition planets exactly into strongly connected components
* Optimality:   k must equal the SCC count from ans
* Complexity:   O(n + m) time, O(n + m) memory
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

static vector<int> compute_scc(const vector<vector<int>>& g, const vector<vector<int>>& rg, int& compCnt) {
int n = (int)g.size() - 1;

vector<int> order = finish_order_iterative(g);
vector<int> comp(n + 1, 0);

compCnt = 0;

for (int it = n - 1; it >= 0; it--) {
    int start = order[it];
    if (comp[start]) continue;

    ++compCnt;

    vector<int> st;
    st.push_back(start);
    comp[start] = compCnt;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (int v : rg[u]) {
            if (!comp[v]) {
                comp[v] = compCnt;
                st.push_back(v);
            }
        }
    }
}

return comp;

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

int ansK = ans.readInt();

int k = ouf.readInt(1, n, "number of kingdoms");
if (k != ansK) {
    quitf(_wa, "contestant printed %d kingdoms, but correct count is %d", k, ansK);
}

vector<int> label(n + 1);
vector<char> used(k + 1, 0);

for (int i = 1; i <= n; i++) {
    label[i] = ouf.readInt(1, k, format("kingdom[%d]", i).c_str());
    used[label[i]] = 1;
}

for (int x = 1; x <= k; x++) {
    if (!used[x]) {
        quitf(_wa, "kingdom label %d is not assigned to any planet", x);
    }
}

int compCnt = 0;
vector<int> comp = compute_scc(g, rg, compCnt);

if (compCnt != ansK) {
    quitf(_fail, "computed SCC count %d differs from jury answer %d", compCnt, ansK);
}

vector<int> compLabel(compCnt + 1, -1);
vector<int> labelComp(k + 1, -1);

for (int planet = 1; planet <= n; planet++) {
    int c = comp[planet];
    int l = label[planet];

    if (compLabel[c] == -1) {
        compLabel[c] = l;
    } else if (compLabel[c] != l) {
        quitf(_wa, "planets in the same SCC have different labels");
    }

    if (labelComp[l] == -1) {
        labelComp[l] = c;
    } else if (labelComp[l] != c) {
        quitf(_wa, "same kingdom label is used for planets in different SCCs");
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid kingdom assignment with %d kingdoms", k);

}
