/*
 * Problem:      2427 Letter Pair Move Game
 * Input read:   n; string of length 2n over A, B, .
 * Validity:     -1 iff no solution; else k moves with k <= 1000, each move is a
 *               valid letter-pair slide preserving order, final state has all A
 *               before all B
 * Optimality:   bound only — k must satisfy 0 <= k <= 1000 (statement bound),
 *               NOT compared to jury move count
 * Complexity:   O(k * n^2)
 */
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
        quitf(_fail, "Input string length %d, expected %d", (int)start.size(), len);

    string ansFirst = ans.readToken();
    if (ansFirst == "-1") {
        string tok = ouf.readToken();
        if (tok != "-1")
            quitf(_wa, "Jury answer is -1 but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported no solution");
    }

    int k = ouf.readInt(0, 1000, "k");
    string state = start;
    for (int move = 0; move < k; move++) {
        string moveStr = ouf.readToken();
        if ((int)moveStr.size() != len)
            quitf(_wa, "Move %d: string must have length %d, got %d",
                  move + 1, len, (int)moveStr.size());
        for (char c : moveStr) {
            if (c != 'A' && c != 'B' && c != '.')
                quitf(_wa, "Move %d: invalid character '%c'", move + 1, c);
        }
        if (!apply_move(state, moveStr))
            quitf(_wa, "Move %d is not a valid letter-pair move from previous state", move + 1);
    }

    if (!is_sorted(state))
        quitf(_wa, "Final state has A after B: %s", state.c_str());

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid solution with %d moves", k);
}
