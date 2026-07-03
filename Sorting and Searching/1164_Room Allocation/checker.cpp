#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        intervals[i] = {a, b};
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Minimum rooms is %d, got %d", k_ans, k);
    ouf.readEoln();

    vector<int> room(n);
    for (int i = 0; i < n; i++) {
        room[i] = ouf.readInt();
        if (room[i] < 1 || room[i] > k)
            quitf(_wa, "Room %d for customer %d out of range [1,%d]", room[i], i + 1, k);
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    vector<vector<int>> by_room(k + 1);
    for (int i = 0; i < n; i++)
        by_room[room[i]].push_back(i);

    for (int r = 1; r <= k; r++) {
        auto& cust = by_room[r];
        sort(cust.begin(), cust.end(), [&](int i, int j) {
            if (intervals[i].first != intervals[j].first)
                return intervals[i].first < intervals[j].first;
            return intervals[i].second < intervals[j].second;
        });
        for (int j = 1; j < (int)cust.size(); j++) {
            int prev = cust[j - 1];
            int cur = cust[j];
            if (intervals[prev].second >= intervals[cur].first)
                quitf(_wa,
                      "Customers %d [%d,%d] and %d [%d,%d] overlap in room %d",
                      prev + 1, intervals[prev].first, intervals[prev].second,
                      cur + 1, intervals[cur].first, intervals[cur].second, r);
        }
    }

    quitf(_ok, "Valid allocation with %d rooms", k);
}
