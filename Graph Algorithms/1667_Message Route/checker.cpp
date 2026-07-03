#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    string ansFirst = ans.readToken();
    string outFirst = ouf.readToken();

    if (outFirst == "IMPOSSIBLE") {
        if (ansFirst != "IMPOSSIBLE")
            quitf(_wa, "Output is IMPOSSIBLE but a route exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no route");
    }

    if (ansFirst == "IMPOSSIBLE")
        quitf(_wa, "A route exists but output is IMPOSSIBLE");

    int minK = stoi(ansFirst);
    int k = stoi(outFirst);
    if (k < 1)
        quitf(_wa, "Route length must be at least 1, got %d", k);

    vector<int> route(k);
    for (int i = 0; i < k; i++) {
        route[i] = ouf.readInt();
        if (route[i] < 1 || route[i] > n)
            quitf(_wa, "City %d out of range", route[i]);
    }

    if (k != minK)
        quitf(_wa, "Route length %d is not minimum (optimal is %d)", k, minK);

    if (route[0] != 1)
        quitf(_wa, "Route must start at city 1, starts at %d", route[0]);
    if (route[k - 1] != n)
        quitf(_wa, "Route must end at city %d, ends at %d", n, route[k - 1]);

    for (int i = 0; i + 1 < k; i++) {
        int u = route[i], v = route[i + 1];
        bool found = false;
        for (int w : g[u])
            if (w == v) {
                found = true;
                break;
            }
        if (!found)
            quitf(_wa, "No connection between %d and %d", u, v);
    }

    for (int i = 0; i < minK; i++)
        ans.readInt();

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid shortest route of length %d", k);
}
