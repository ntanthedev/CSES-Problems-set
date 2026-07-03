/*

* Problem:      3308 Graph Coloring
* Input read:   n, m; m undirected edges
* Validity:     Output k colors and n color labels in [1,k]; adjacent nodes must have
* ```
            different colors
* Optimality:   k must equal the minimum number of colors from ans
* Complexity:   O(n + m) time, O(n + m) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();

vector<pair<int, int>> edges;
edges.reserve(m);

for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    edges.push_back({a, b});
}

int optimal = ans.readInt();

int k = ouf.readInt(1, n, "number of colors");
if (k != optimal) {
    quitf(_wa, "contestant printed %d colors, but optimum is %d", k, optimal);
}

vector<int> color(n + 1);

for (int i = 1; i <= n; i++) {
    color[i] = ouf.readInt(1, k, format("color[%d]", i).c_str());
}

for (auto [a, b] : edges) {
    if (color[a] == color[b]) {
        quitf(_wa, "edge %d-%d connects nodes with the same color %d",
              a, b, color[a]);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid optimal coloring with %d colors", k);

}
