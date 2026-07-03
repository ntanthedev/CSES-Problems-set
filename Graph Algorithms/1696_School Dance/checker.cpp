/*

* Problem:      1696 School Dance
* Input read:   n, m, k; k possible boy-girl pairs
* Validity:     Output r valid potential pairs, with no boy or girl used more than once
* Optimality:   r must equal the maximum matching size from ans
* Complexity:   O(k + r) expected time, O(n + m + k) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

static long long pair_key(int boy, int girl, int m) {
return 1LL * boy * (m + 1LL) + girl;
}

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();
int m = inf.readInt();
int kInput = inf.readInt();

unordered_set<long long> possible;
possible.reserve((size_t)kInput * 2 + 10);

for (int i = 0; i < kInput; i++) {
    int a = inf.readInt();
    int b = inf.readInt();

    possible.insert(pair_key(a, b, m));
}

int optimal = ans.readInt();

int r = ouf.readInt(0, min(n, m), "number of pairs");
if (r != optimal) {
    quitf(_wa, "contestant printed %d pairs, but optimum is %d", r, optimal);
}

vector<char> usedBoy(n + 1, 0);
vector<char> usedGirl(m + 1, 0);

unordered_set<long long> answerPairs;
answerPairs.reserve((size_t)r * 2 + 10);

for (int i = 1; i <= r; i++) {
    int boy = ouf.readInt(1, n, format("pair[%d].boy", i).c_str());
    int girl = ouf.readInt(1, m, format("pair[%d].girl", i).c_str());

    long long key = pair_key(boy, girl, m);

    if (!possible.count(key)) {
        quitf(_wa, "pair (%d,%d) is not a potential pair", boy, girl);
    }

    if (answerPairs.count(key)) {
        quitf(_wa, "pair (%d,%d) is listed more than once", boy, girl);
    }

    if (usedBoy[boy]) {
        quitf(_wa, "boy %d is paired more than once", boy);
    }

    if (usedGirl[girl]) {
        quitf(_wa, "girl %d is paired more than once", girl);
    }

    answerPairs.insert(key);
    usedBoy[boy] = 1;
    usedGirl[girl] = 1;
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid maximum matching of size %d", r);

}
