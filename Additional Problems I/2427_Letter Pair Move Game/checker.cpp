#include "testlib.h"
#include <string>
using namespace std;

static bool apply_move(string& state, const string& next) {
    int len = (int)state.size();
    for (int i = 0; i < len - 1; i++) {
        if (state[i] == '.' || state[i + 1] == '.') continue;
        for (int e = 0; e < len - 1; e++) {
            if (state[e] != '.' || state[e + 1] != '.') continue;
            string expected = state;
            expected[e] = state[i];
            expected[e + 1] = state[i + 1];
            expected[i] = '.';
            expected[i + 1] = '.';
            if (expected == next) {
                state = next;
                return true;
            }
        }
    }
    return false;
}

static bool is_sorted(const string& state) {
    bool seenB = false;
    for (char c : state) {
        if (c == 'B') seenB = true;
        if (c == 'A' && seenB) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string start = inf.readToken();
    int len = 2 * n;
    if ((int)start.size() != len)
        quitf(_wa, "Input string length mismatch");

    string ans_first = ans.readToken();
    bool ans_impossible = (ans_first == "-1");

    string token = ouf.readToken();
    if (token == "-1") {
        if (!ans_impossible)
            quitf(_wa, "A solution exists but contestant printed -1");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no solution");
    }

    if (ans_impossible)
        quitf(_wa, "No solution exists but contestant printed moves");

    int k_ans = stoi(ans_first);
    int k = stoi(token);
    if (k < 0 || k > 1000)
        quitf(_wa, "Number of moves k must be between 0 and 1000, got %d", k);
    if (k != k_ans)
        quitf(_wa, "Claimed %d moves but optimal is %d", k, k_ans);

    string state = start;
    for (int move = 0; move < k; move++) {
        string moveStr = ouf.readToken();
        if ((int)moveStr.size() != len)
            quitf(_wa, "Move %d: string must have length %d, got %d",
                  move + 1, len, (int)moveStr.size());
        if (!apply_move(state, moveStr))
            quitf(_wa, "Move %d is not a valid letter-pair move from previous state", move + 1);
    }

    if (!is_sorted(state))
        quitf(_wa, "Final state has A after B: %s", state.c_str());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal solution with %d moves", k);
}
