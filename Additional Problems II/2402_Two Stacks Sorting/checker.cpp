#include "testlib.h"
#include <vector>
#include <string>
#include <stack>
using namespace std;

static bool simulate(const vector<int>& input, const vector<int>& assignment) {
    stack<int> s1, s2;
    int next_output = 1;
    int input_pos = 0;

    while (next_output <= (int)input.size()) {
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
        if (input_pos >= (int)input.size()) return false;

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

    string ans_first = ans.readToken();
    bool ans_impossible = (ans_first == "IMPOSSIBLE");

    string first = ouf.readToken();
    if (first == "IMPOSSIBLE") {
        if (!ans_impossible)
            quitf(_wa, "Output is IMPOSSIBLE but a valid assignment exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported IMPOSSIBLE");
    }

    if (ans_impossible)
        quitf(_wa, "A valid assignment exists but output is IMPOSSIBLE");

    vector<int> assignment(n);
    assignment[0] = stoi(first);
    if (assignment[0] != 1 && assignment[0] != 2)
        quitf(_wa, "Stack assignment must be 1 or 2, got %d", assignment[0]);
    for (int i = 1; i < n; i++) {
        assignment[i] = ouf.readInt();
        if (assignment[i] != 1 && assignment[i] != 2)
            quitf(_wa, "Stack assignment must be 1 or 2, got %d at position %d",
                  assignment[i], i + 1);
    }

    if (!simulate(input, assignment))
        quitf(_wa, "Invalid two-stack sorting assignment");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid two-stack sorting");
}
