/*

* Problem:      1682 Flight Routes Check
* Input read:   n, m; m directed flights
* Validity:     YES iff the graph is strongly connected according to ans; otherwise NO
* ```
            followed by two cities a,b such that b is not reachable from a
* Optimality:   Feasibility is taken from ans; any valid counterexample is accepted
* Complexity:   O(n + m) time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

vector<vector<int>> g(n + 1);
for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    g[a].push_back(b);
}

string ansFlag = ans.readToken();
if (ansFlag != "YES" && ansFlag != "NO") {
    quitf(_fail, "malformed jury answer token '%s'", compress(ansFlag).c_str());
}

string outFlag = ouf.readToken();
if (outFlag != "YES" && outFlag != "NO") {
    quitf(_wa, "expected YES or NO, got '%s'", compress(outFlag).c_str());
}

if (outFlag == "YES") {
    if (ansFlag != "YES") {
        quitf(_wa, "contestant printed YES, but not all routes are possible");
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported YES");
}

if (ansFlag == "YES") {
    quitf(_wa, "contestant printed NO, but all routes are possible");
}

int a = ouf.readInt(1, n, "counterexample start city");
int b = ouf.readInt(1, n, "counterexample target city");

vector<char> vis(n + 1, 0);
queue<int> q;
q.push(a);
vis[a] = 1;

while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : g[u]) {
        if (!vis[v]) {
            vis[v] = 1;
            q.push(v);
        }
    }
}

if (vis[b]) {
    quitf(_wa, "city %d is reachable from city %d, so it is not a valid counterexample",
          b, a);
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid counterexample: city %d cannot reach city %d", a, b);

}
