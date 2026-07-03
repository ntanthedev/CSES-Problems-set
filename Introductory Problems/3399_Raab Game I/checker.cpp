#include "testlib.h"
#include <vector>
using namespace std;

static void consume_game(int n, InStream& stream) {
    for (int i = 0; i < n; i++)
        stream.readInt();
    for (int i = 0; i < n; i++)
        stream.readInt();
}

static void validate_game(int n, int a, int b) {
    vector<int> p1(n), p2(n);
    for (int i = 0; i < n; i++)
        p1[i] = ouf.readInt();
    for (int i = 0; i < n; i++)
        p2[i] = ouf.readInt();

    vector<bool> seen1(n + 1, false), seen2(n + 1, false);
    for (int i = 0; i < n; i++) {
        if (p1[i] < 1 || p1[i] > n)
            quitf(_wa, "P1[%d]=%d out of range [1,%d]", i + 1, p1[i], n);
        if (seen1[p1[i]])
            quitf(_wa, "P1 duplicate value %d", p1[i]);
        seen1[p1[i]] = true;

        if (p2[i] < 1 || p2[i] > n)
            quitf(_wa, "P2[%d]=%d out of range [1,%d]", i + 1, p2[i], n);
        if (seen2[p2[i]])
            quitf(_wa, "P2 duplicate value %d", p2[i]);
        seen2[p2[i]] = true;
    }

    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; i++) {
        if (p1[i] > p2[i])
            s1++;
        else if (p1[i] < p2[i])
            s2++;
    }

    if (s1 != a || s2 != b)
        quitf(_wa, "Expected scores (%d,%d) but got (%d,%d)", a, b, s1, s2);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 0; tc < t; tc++) {
        int n = inf.readInt();
        int a = inf.readInt();
        int b = inf.readInt();
        string ans_flag = ans.readToken();
        string ouf_flag = ouf.readToken();

        if (ans_flag == "NO") {
            if (ouf_flag != "NO")
                quitf(_wa, "Test %d: no valid game exists but contestant printed '%s'", tc + 1, ouf_flag.c_str());
            continue;
        }

        if (ans_flag != "YES")
            quitf(_fail, "Test %d: judge answer malformed, expected YES or NO", tc + 1);

        if (ouf_flag == "NO")
            quitf(_wa, "Test %d: a valid game exists but contestant printed NO", tc + 1);
        if (ouf_flag != "YES")
            quitf(_wa, "Test %d: expected YES or NO, got '%s'", tc + 1, ouf_flag.c_str());

        consume_game(n, ans);
        validate_game(n, a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid for %d test cases", t);
}
