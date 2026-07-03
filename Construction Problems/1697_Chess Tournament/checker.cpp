#include "testlib.h"
#include <vector>
using namespace std;

static void consume_games(int k, InStream& stream) {
    for (int i = 0; i < k; i++) {
        stream.readInt();
        stream.readInt();
    }
}

static void validate_tournament(int n, int k, const vector<int>& deg) {
    if (k < 0)
        quitf(_wa, "Number of games must be non-negative, got %d", k);

    vector<vector<bool>> played(n + 1, vector<bool>(n + 1, false));
    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Player %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "Player %d out of range", b);
        if (a == b)
            quitf(_wa, "Player cannot play against themselves: %d %d", a, b);
        if (played[a][b])
            quitf(_wa, "Pair %d %d plays more than once", a, b);
        played[a][b] = played[b][a] = true;
        cnt[a]++;
        cnt[b]++;
    }

    for (int i = 1; i <= n; i++) {
        if (cnt[i] != deg[i])
            quitf(_wa, "Player %d wanted %d games but got %d", i, deg[i], cnt[i]);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i++)
        deg[i] = inf.readInt();
    string ans_first = ans.readToken();
    string ouf_first = ouf.readToken();

    if (ans_first == "IMPOSSIBLE") {
        if (ouf_first != "IMPOSSIBLE")
            quitf(_wa, "No valid tournament exists but contestant printed '%s'", ouf_first.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no valid tournament");
    }

    if (ouf_first == "IMPOSSIBLE")
        quitf(_wa, "A valid tournament exists but contestant printed IMPOSSIBLE");

    int k_ans = stoi(ans_first);
    consume_games(k_ans, ans);

    int k = stoi(ouf_first);
    validate_tournament(n, k, deg);
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid tournament with %d games", k);
}
