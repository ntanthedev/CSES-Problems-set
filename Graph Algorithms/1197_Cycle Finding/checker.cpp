/*

* Problem:      1197 Cycle Finding
* Input read:   n, m; m directed weighted edges
* Validity:     NO iff jury says no negative cycle; otherwise YES followed by a vertex
* ```
            sequence whose first and last vertices match, every consecutive directed
* ```
            edge exists, and the minimum possible total weight along the sequence is negative
* Optimality:   Feasibility is taken from ans; any valid negative cycle is accepted
* Complexity:   O(m + n) expected time, O(m + n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

using ll = long long;

static long long edge_key(int u, int v, int n) {
return 1LL * u * (n + 1LL) + v;
}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

unordered_map<long long, ll> bestWeight;
bestWeight.reserve((size_t)m * 2 + 10);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    ll c = inf.readLong();

    long long key = edge_key(a, b, n);
    auto it = bestWeight.find(key);
    if (it == bestWeight.end() || c < it->second) {
        bestWeight[key] = c;
    }
}

string ansToken = ans.readToken();
if (ansToken != "YES" && ansToken != "NO") {
    quitf(_fail, "malformed jury answer token '%s'", compress(ansToken).c_str());
}

string outToken = ouf.readToken();
if (outToken != "YES" && outToken != "NO") {
    quitf(_wa, "expected YES or NO, got '%s'", compress(outToken).c_str());
}

if (ansToken == "NO") {
    if (outToken != "NO") {
        quitf(_wa, "jury says there is no negative cycle, but contestant printed YES");
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported NO");
}

if (outToken == "NO") {
    quitf(_wa, "a negative cycle exists, but contestant printed NO");
}

vector<int> cycle;
while (!ouf.seekEof()) {
    if ((int)cycle.size() == n + 1) {
        quitf(_wa, "cycle contains more than %d vertices", n + 1);
    }
    cycle.push_back(ouf.readInt(1, n, format("cycle[%d]", (int)cycle.size() + 1).c_str()));
}

if ((int)cycle.size() < 2) {
    quitf(_wa, "cycle must contain at least two listed vertices");
}

if (cycle.front() != cycle.back()) {
    quitf(_wa, "cycle must start and end at the same vertex, got %d and %d",
          cycle.front(), cycle.back());
}

vector<char> seen(n + 1, 0);
for (int i = 0; i + 1 < (int)cycle.size(); i++) {
    int v = cycle[i];
    if (seen[v]) {
        quitf(_wa, "vertex %d appears more than once before the final return", v);
    }
    seen[v] = 1;
}

ll total = 0;
for (int i = 0; i + 1 < (int)cycle.size(); i++) {
    int u = cycle[i];
    int v = cycle[i + 1];

    auto it = bestWeight.find(edge_key(u, v, n));
    if (it == bestWeight.end()) {
        quitf(_wa, "no directed edge from %d to %d at cycle step %d", u, v, i + 1);
    }

    total += it->second;
}

if (total >= 0) {
    quitf(_wa, "cycle total weight is %lld, not negative", total);
}

quitf(_ok, "valid negative cycle with total weight %lld", total);

}
