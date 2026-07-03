#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> teleporters;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        teleporters.push_back({a, b});
    }

    int maxDays = ans.readInt();
    int k = ouf.readInt();
    if (k < 0 || k > m)
        quitf(_wa, "Number of days %d out of range [0,%d]", k, m);

    if (k != maxDays)
        quitf(_wa, "Found %d day routes but optimal is %d", k, maxDays);

    set<pair<int, int>> usedEdges;
    for (int day = 0; day < k; day++) {
        int len = ouf.readInt();
        if (len < 2)
            quitf(_wa, "Day %d path length %d too short", day + 1, len);

        vector<int> path(len);
        for (int i = 0; i < len; i++) {
            path[i] = ouf.readInt();
            if (path[i] < 1 || path[i] > n)
                quitf(_wa, "Room %d out of range on day %d", path[i], day + 1);
        }

        if (path[0] != 1)
            quitf(_wa, "Day %d path must start at room 1", day + 1);
        if (path[len - 1] != n)
            quitf(_wa, "Day %d path must end at room %d", day + 1, n);

        for (int i = 0; i + 1 < len; i++) {
            int u = path[i], v = path[i + 1];
            pair<int, int> edge = {u, v};
            bool exists = false;
            for (auto tp : teleporters)
                if (tp == edge) {
                    exists = true;
                    break;
                }
            if (!exists)
                quitf(_wa, "No teleporter from %d to %d (day %d)", u, v, day + 1);
            if (usedEdges.count(edge))
                quitf(_wa, "Teleporter %d->%d used more than once", u, v);
            usedEdges.insert(edge);
        }

        int ansLen = ans.readInt();
        for (int i = 0; i < ansLen; i++)
            ans.readInt();
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid %d edge-disjoint routes", k);
}
