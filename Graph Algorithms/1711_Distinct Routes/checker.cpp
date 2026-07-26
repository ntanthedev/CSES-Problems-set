/*
Problem: 1711 Distinct Routes
Input read: n, m; m directed teleporters
Validity: First output k, then k routes. Each route starts at 1, ends at n,
          follows existing teleporters, and no teleporter is used twice globally 
Optimality: k must equal the maximum number of routes from ans
Complexity: O(n + m + total output route length) expected time, O(n + m) memory
*/
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
static long long edge_key(int u, int v, int n) {
return 1LL * u * (n + 1LL) + v;
}
int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);
int n = inf.readInt(); int m = inf.readInt();  unordered_set<long long> edges; edges.reserve((size_t)m * 2 + 10);  for (int i = 0; i < m; i++) {     int a = inf.readInt();     int b = inf.readInt();     edges.insert(edge_key(a, b, n)); }  int optimalDays = ans.readInt();  int k = ouf.readInt(0, m, "number of routes"); if (k != optimalDays) {     quitf(_wa, "contestant printed %d routes, but optimum is %d", k, optimalDays); }  unordered_set<long long> usedEdges; usedEdges.reserve((size_t)m * 2 + 10);  for (int day = 1; day <= k; day++) {     int len = ouf.readInt(2, m + 1, format("route[%d].length", day).c_str());      vector<int> route(len);     for (int i = 0; i < len; i++) {         route[i] = ouf.readInt(1, n, format("route[%d].city[%d]", day, i + 1).c_str());     }      if (route.front() != 1) {         quitf(_wa, "route %d must start at room 1, but starts at room %d",               day, route.front());     }      if (route.back() != n) {         quitf(_wa, "route %d must end at room %d, but ends at room %d",               day, n, route.back());     }      for (int i = 0; i + 1 < len; i++) {         int u = route[i];         int v = route[i + 1];         long long key = edge_key(u, v, n);          if (!edges.count(key)) {             quitf(_wa, "route %d uses nonexistent teleporter %d -> %d at step %d",                   day, u, v, i + 1);         }          if (usedEdges.count(key)) {             quitf(_wa, "teleporter %d -> %d is used more than once", u, v);         }          usedEdges.insert(key);     } }  if (!ouf.seekEof())     quitf(_wa, "extra information in the output file");  quitf(_ok, "valid set of %d edge-disjoint routes", k); 
}
