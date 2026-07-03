#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    int k_req = inf.readInt();
    vector<set<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].insert(b);
    }

    int ans_first = ans.readInt();
    bool impossible = (ans_first == -1);

    int first_val = ouf.readInt();
    if (first_val == -1) {
        if (!impossible)
            quitf(_wa, "Output is -1 but playing for %d days is possible", k_req);
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported impossible");
    }

    if (impossible)
        quitf(_wa, "Expected -1 (impossible), but contestant claimed %d coins", first_val);

    int total_coins = first_val;
    if (total_coins != ans_first)
        quitf(_wa, "Minimum number of coins is %d, got %d", ans_first, total_coins);
    if (total_coins < 0)
        quitf(_wa, "Total coins must be non-negative");

    set<pair<int, int>> used_edges;
    int actual_total_len = 0;

    for (int day = 0; day < k_req; day++) {
        int route_len = ouf.readInt();
        if (route_len < 1)
            quitf(_wa, "Route length must be at least 1");

        vector<int> route(route_len);
        for (int i = 0; i < route_len; i++) {
            route[i] = ouf.readInt();
            if (route[i] < 1 || route[i] > n)
                quitf(_wa, "Room %d out of range", route[i]);
        }

        if (route[0] != 1)
            quitf(_wa, "Route must start at room 1, starts at %d", route[0]);
        if (route[route_len - 1] != n)
            quitf(_wa, "Route must end at room n, ends at %d", route[route_len - 1]);

        for (int i = 0; i + 1 < route_len; i++) {
            int a = route[i], b = route[i + 1];
            if (!g[a].count(b))
                quitf(_wa, "Teleporter %d -> %d does not exist", a, b);
            pair<int, int> key = {a, b};
            if (used_edges.count(key))
                quitf(_wa, "Teleporter %d -> %d used more than once", a, b);
            used_edges.insert(key);
            actual_total_len++;
        }
    }

    if (actual_total_len != total_coins)
        quitf(_wa, "Claimed total coins %d, but sum of route lengths is %d",
              total_coins, actual_total_len);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal %d routes, total %d coins", k_req, total_coins);
}
