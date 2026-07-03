/*
 * Problem:      2402 Two Stacks Sorting
 * Input read:   n; permutation input[1..n]
 * Validity:     IMPOSSIBLE iff unsortable; else n stack labels (1 or 2) such that
 *               simulating two-stack sorting produces 1..n in order
 * Optimality:   any valid assignment (no scalar from ans)
 * Complexity:   O(n)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <stack>
using namespace std;

static bool simulate(const vector<int>& input, const vector<int>& assignment) {
    stack<int> s1, s2;
    int next_output = 1;
    int input_pos = 0;
    int n = (int)input.size();

    while (next_output <= n) {
        if (!s1.empty() && s1.top() == next_output) {
            s1.pop();
            next_output++;
            continue;
        }
        if (!s2.empty() && s2.top() == next_output) {
            s2.pop();
            next_output++;
            continue;
        }
        if (input_pos >= n) return false;

        int val = input[input_pos];
        int st = assignment[input_pos++];
        if (st == 1) {
            if (!s1.empty() && val > s1.top()) return false;
            s1.push(val);
        } else if (st == 2) {
            if (!s2.empty() && val > s2.top()) return false;
            s2.push(val);
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> input(n);
    for (int i = 0; i < n; i++)
        input[i] = inf.readInt();

    string ansFirst = ans.readToken();
    if (ansFirst == "IMPOSSIBLE") {
        string tok = ouf.readToken();
        if (tok != "IMPOSSIBLE")
            quitf(_wa, "Jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    string oufFirst = ouf.readToken();
    if (oufFirst == "IMPOSSIBLE")
        quitf(_wa, "jury has a valid two-stack assignment but contestant printed IMPOSSIBLE");

    auto readStack = [&](const string &t, const char *name) -> int {
        if (t.size() != 1 || (t[0] != '1' && t[0] != '2'))
            quitf(_wa, "%s must be 1 or 2, got \"%s\"", name, compress(t).c_str());
        return t[0] - '0';
    };

    vector<int> assignment(n);
    assignment[0] = readStack(oufFirst, "stack[1]");
    for (int i = 1; i < n; i++)
        assignment[i] = ouf.readInt(1, 2, format("stack[%d]", i + 1).c_str());

    if (!simulate(input, assignment))
        quitf(_wa, "Invalid two-stack sorting assignment");

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid two-stack sorting");
}
