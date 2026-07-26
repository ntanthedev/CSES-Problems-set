/*
Problem: 1680 Longest Flight Route
Input read: n, m; m directed flights
Validity: IMPOSSIBLE iff jury says no route; otherwise k cities, starting at 1,
          ending at n, and every consecutive pair is an input flight 
Optimality: k must equal the maximum route length from ans
Complexity: O(n + m) expected time, O(n + m) memory
*/
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
static long long edge_key(int u, int v, int n) {
return 1LL * u * (n + 1LL) + v;
}
static int parse_jury_int_token(const string& tok, int lo, int hi, const char* name) {
long long val = 0;
if (tok.empty()) {
quitf(_fail, "jury token for %s is empty", name);
}
for (char ch : tok) {     if (ch < '0' || ch > '9') {         quitf(_fail, "jury token for %s is not a non-negative integer: '%s'",               name, compress(tok).c_str());     }     val = val * 10 + (ch - '0');     if (val > hi) {         quitf(_fail, "jury value for %s is too large: %lld > %d", name, val, hi);     } }  if (val < lo) {     quitf(_fail, "jury value for %s is too small: %lld < %d", name, val, lo); }  return (int)val; 
}
int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);
int n = inf.readInt(); int m = inf.readInt();  unordered_set<long long> edges; edges.reserve((size_t)m * 2 + 10);  for (int i = 0; i < m; i++) {     int a = inf.readInt();     int b = inf.readInt();     edges.insert(edge_key(a, b, n)); }  string ansFirst = ans.readToken();  if (ansFirst == "IMPOSSIBLE") {     string outFirst = ouf.readToken();     if (outFirst != "IMPOSSIBLE") {         quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed '%s'",               compress(outFirst).c_str());     }      if (!ouf.seekEof())         quitf(_wa, "extra information in the output file");      quitf(_ok, "correctly reported IMPOSSIBLE"); }  int optimal = parse_jury_int_token(ansFirst, 1, n, "maximum route length");  int k = ouf.readInt(1, n, "route length"); if (k != optimal) {     quitf(_wa, "route length is %d, but the maximum length is %d", k, optimal); }  vector<int> route(k); for (int i = 0; i < k; i++) {     route[i] = ouf.readInt(1, n, format("city[%d]", i + 1).c_str()); }  if (route.front() != 1) {     quitf(_wa, "route must start at city 1, but starts at city %d", route.front()); }  if (route.back() != n) {     quitf(_wa, "route must end at city %d, but ends at city %d", n, route.back()); }  for (int i = 0; i + 1 < k; i++) {     int u = route[i];     int v = route[i + 1];      if (!edges.count(edge_key(u, v, n))) {         quitf(_wa, "no flight from city %d to city %d at step %d", u, v, i + 1);     } }  if (!ouf.seekEof())     quitf(_wa, "extra information in the output file");  quitf(_ok, "valid longest route of length %d", k); 
}
