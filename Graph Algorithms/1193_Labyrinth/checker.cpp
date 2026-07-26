/*
Problem: 1193 Labyrinth
Input read: n, m; n grid rows
Validity: NO iff jury says unreachable; otherwise YES, shortest length, and a path string
          over L/R/U/D that moves from A to B without leaving the grid or entering walls 
Optimality: Path length must equal the shortest length from ans
Complexity: O(nm + path length) time, O(nm) memory
*/
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);
int n = inf.readInt(); int m = inf.readInt();  vector<string> grid(n); pair<int, int> start = {-1, -1}; pair<int, int> target = {-1, -1};  for (int i = 0; i < n; i++) {     grid[i] = inf.readToken();      if ((int)grid[i].size() != m) {         quitf(_fail, "input row %d has length %d, expected %d",               i + 1, (int)grid[i].size(), m);     }      for (int j = 0; j < m; j++) {         if (grid[i][j] == 'A') start = {i, j};         if (grid[i][j] == 'B') target = {i, j};     } }  if (start.first == -1 || target.first == -1) {     quitf(_fail, "input must contain exactly one A and one B"); }  string ansFlag = ans.readToken(); if (ansFlag != "YES" && ansFlag != "NO") {     quitf(_fail, "malformed jury answer token '%s'", compress(ansFlag).c_str()); }  string outFlag = ouf.readToken(); if (outFlag != "YES" && outFlag != "NO") {     quitf(_wa, "expected YES or NO, got '%s'", compress(outFlag).c_str()); }  if (ansFlag == "NO") {     if (outFlag != "NO") {         quitf(_wa, "jury says no path exists, but contestant printed YES");     }      if (!ouf.seekEof())         quitf(_wa, "extra information in the output file");      quitf(_ok, "correctly reported NO"); }  if (outFlag == "NO") {     quitf(_wa, "a path exists, but contestant printed NO"); }  int shortest = ans.readInt();  int maxLen = n * m; int len = ouf.readInt(1, maxLen, "path length");  if (len != shortest) {     quitf(_wa, "path length is %d, but shortest path length is %d", len, shortest); }  string pattern = format("[LRUD]{%d}", len); string path = ouf.readToken(pattern, "path");  int r = start.first; int c = start.second;  for (int i = 0; i < len; i++) {     char ch = path[i];      if (ch == 'L') c--;     else if (ch == 'R') c++;     else if (ch == 'U') r--;     else if (ch == 'D') r++;     else quitf(_wa, "invalid direction '%c' at step %d", ch, i + 1);      if (r < 0 || r >= n || c < 0 || c >= m) {         quitf(_wa, "path leaves the grid after step %d", i + 1);     }      if (grid[r][c] == '#') {         quitf(_wa, "path enters a wall at row %d column %d after step %d",               r + 1, c + 1, i + 1);     } }  if (make_pair(r, c) != target) {     quitf(_wa, "path ends at row %d column %d, but target is row %d column %d",           r + 1, c + 1, target.first + 1, target.second + 1); }  if (!ouf.seekEof())     quitf(_wa, "extra information in the output file");  quitf(_ok, "valid shortest path of length %d", len); 
}
