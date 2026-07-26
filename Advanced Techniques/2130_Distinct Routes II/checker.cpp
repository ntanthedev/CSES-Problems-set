/*
Problem: 2130 Distinct Routes II
Input read: n, m, k; m directed teleporters
Validity: -1 iff jury says impossible; otherwise total cost followed by exactly k routes.
          Each route starts at 1, ends at n, follows existing teleporters, and no 
          teleporter is used twice globally 
Optimality: Total cost must equal the minimum cost from ans
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
int n = inf.readInt(); int m = inf.readInt(); int requiredRoutes = inf.readInt();  unordered_set<long long> edges; edges.reserve((size_t)m * 2 + 10);  for (int i = 0; i < m; i++) {     int a = inf.readInt();     int b = inf.readInt();     edges.insert(edge_key(a, b, n)); }  int optimalCost = ans.readInt();  if (optimalCost == -1) {     int outFirst = ouf.readInt(-1, m, "answer");      if (outFirst != -1) {         quitf(_wa, "jury answer is -1, but contestant claimed cost %d", outFirst);     }      if (!ouf.seekEof())         quitf(_wa, "extra information in the output file");      quitf(_ok, "correctly reported impossible"); }  if (optimalCost < 0 || optimalCost > m) {     quitf(_fail, "jury answer has invalid optimal cost %d", optimalCost); }  int totalCost = ouf.readInt(-1, m, "minimum cost");  if (totalCost == -1) {     quitf(_wa, "contestant printed -1, but playing for %d days is possible", requiredRoutes); }  if (totalCost != optimalCost) {     quitf(_wa, "contestant cost is %d, but optimal cost is %d", totalCost, optimalCost); }  unordered_set<long long> usedEdges; usedEdges.reserve((size_t)m * 2 + 10);  int actualCost = 0;  for (int day = 1; day <= requiredRoutes; day++) {     int len = ouf.readInt(2, m + 1, format("route[%d].length", day).c_str());      vector<int> route(len);     for (int i = 0; i < len; i++) {         route[i] = ouf.readInt(1, n, format("route[%d].city[%d]", day, i + 1).c_str());     }      if (route.front() != 1) {         quitf(_wa, "route %d must start at room 1, but starts at room %d",               day, route.front());     }      if (route.back() != n) {         quitf(_wa, "route %d must end at room %d, but ends at room %d",               day, n, route.back());     }      for (int i = 0; i + 1 < len; i++) {         int u = route[i];         int v = route[i + 1];         long long key = edge_key(u, v, n);          if (!edges.count(key)) {             quitf(_wa, "route %d uses nonexistent teleporter %d -> %d at step %d",                   day, u, v, i + 1);         }          if (usedEdges.count(key)) {             quitf(_wa, "teleporter %d -> %d is used more than once", u, v);         }          usedEdges.insert(key);         actualCost++;     }      if (actualCost > totalCost) {         quitf(_wa, "used more teleporters than claimed cost %d", totalCost);     } }  if (actualCost != totalCost) {     quitf(_wa, "claimed cost is %d, but routes use %d teleporters", totalCost, actualCost); }  if (!ouf.seekEof())     quitf(_wa, "extra information in the output file");  quitf(_ok, "valid optimal %d routes with total cost %d", requiredRoutes, totalCost); 
}
