/*

* Problem:      3399 Raab Game I
* Input read:   t; for each test n, a, b
* Validity:     For each test, NO iff jury says impossible; otherwise YES followed by two
* ```
            permutations of 1..n whose score is exactly (a,b)
* Optimality:   Feasibility is taken from ans; any valid game is accepted
* Complexity:   O(total n) time, O(n) memory per test
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static void consume_jury_game(int n) {
for (int i = 0; i < n; i++) {
ans.readInt();
}
for (int i = 0; i < n; i++) {
ans.readInt();
}
}

static vector<int> read_permutation(int n, const string& name) {
vector<int> p(n);
vector<char> seen(n + 1, 0);

for (int i = 0; i < n; i++) {
    p[i] = ouf.readInt(1, n, format("%s[%d]", name.c_str(), i + 1).c_str());

    if (seen[p[i]]) {
        quitf(_wa, "%s has duplicate value %d", name.c_str(), p[i]);
    }

    seen[p[i]] = 1;
}

return p;

}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int t = inf.readInt();

for (int tc = 1; tc <= t; tc++) {
    int n = inf.readInt();
    int a = inf.readInt();
    int b = inf.readInt();

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO") {
        quitf(_fail, "test %d: malformed jury answer token '%s'",
              tc, compress(ansFlag).c_str());
    }

    if (ansFlag == "YES") {
        consume_jury_game(n);
    }

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO") {
        quitf(_wa, "test %d: expected YES or NO, got '%s'",
              tc, compress(outFlag).c_str());
    }

    if (ansFlag == "NO") {
        if (outFlag != "NO") {
            quitf(_wa, "test %d: no valid game exists, but contestant printed YES", tc);
        }
        continue;
    }

    if (outFlag == "NO") {
        quitf(_wa, "test %d: a valid game exists, but contestant printed NO", tc);
    }

    vector<int> p1 = read_permutation(n, format("test %d player1", tc));
    vector<int> p2 = read_permutation(n, format("test %d player2", tc));

    int score1 = 0;
    int score2 = 0;

    for (int i = 0; i < n; i++) {
        if (p1[i] > p2[i]) {
            score1++;
        } else if (p1[i] < p2[i]) {
            score2++;
        }
    }

    if (score1 != a || score2 != b) {
        quitf(_wa, "test %d: expected scores (%d,%d), but got (%d,%d)",
              tc, a, b, score1, score2);
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid output for all %d test cases", t);

}
