/*

* Problem:      1070 Permutations
* Input read:   n
* Validity:     NO SOLUTION iff jury says impossible; otherwise a permutation of 1..n
* ```
            where adjacent values never differ by 1
* Optimality:   Feasibility is taken from ans; any valid beautiful permutation is accepted
* Complexity:   O(n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

string ansFirst = ans.readToken();

if (ansFirst == "NO") {
    string ansSecond = ans.readToken();
    if (ansSecond != "SOLUTION") {
        quitf(_fail, "malformed jury answer: expected NO SOLUTION");
    }

    string outFirst = ouf.readToken();
    if (outFirst != "NO") {
        quitf(_wa, "no beautiful permutation exists, but contestant printed '%s'",
              compress(outFirst).c_str());
    }

    string outSecond = ouf.readToken();
    if (outSecond != "SOLUTION") {
        quitf(_wa, "expected NO SOLUTION, got NO %s", compress(outSecond).c_str());
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    quitf(_ok, "correctly reported NO SOLUTION");
}

vector<char> seen(n + 1, 0);

int prev = -1;
for (int pos = 1; pos <= n; pos++) {
    int cur = ouf.readInt(1, n, format("p[%d]", pos).c_str());

    if (seen[cur]) {
        quitf(_wa, "value %d appears more than once", cur);
    }
    seen[cur] = 1;

    if (pos > 1 && abs(cur - prev) == 1) {
        quitf(_wa, "adjacent values at positions %d and %d differ by 1: %d and %d",
              pos - 1, pos, prev, cur);
    }

    prev = cur;
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid beautiful permutation of length %d", n);

}
