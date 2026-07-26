/*

* Problem:      1164 Room Allocation
* Input read:   n; n customer intervals [arrival, departure]
* Validity:     Output the optimal number of rooms k from ans, then one room number in [1,k]
* ```
            for each customer; customers assigned to the same room must not overlap
* Optimality:   k must equal the minimum room count from ans
* Complexity:   O(n log n) time, O(n) memory
  */
  #include "testlib.h"
  #include <bits/stdc++.h>
  using namespace std;

int main(int argc, char* argv[]) {
registerTestlibCmd(argc, argv);

int n = inf.readInt();

vector<pair<long long, long long>> intervals(n);
for (int i = 0; i < n; i++) {
    long long a = inf.readLong();
    long long b = inf.readLong();
    intervals[i] = {a, b};
}

int optimalRooms = ans.readInt();

int k = ouf.readInt(1, n, "number of rooms");

if (k != optimalRooms) {
    quitf(_wa, "contestant printed %d rooms, but minimum is %d",
          k, optimalRooms);
}

vector<int> room(n);
vector<vector<int>> byRoom(k + 1);

for (int i = 0; i < n; i++) {
    room[i] = ouf.readInt(1, k, format("room[%d]", i + 1).c_str());
    byRoom[room[i]].push_back(i);
}

for (int r = 1; r <= k; r++) {
    vector<int>& customers = byRoom[r];

    sort(customers.begin(), customers.end(), [&](int x, int y) {
        if (intervals[x].first != intervals[y].first) {
            return intervals[x].first < intervals[y].first;
        }
        return intervals[x].second < intervals[y].second;
    });

    for (int i = 1; i < (int)customers.size(); i++) {
        int prev = customers[i - 1];
        int cur = customers[i];

        if (intervals[prev].second >= intervals[cur].first) {
            quitf(_wa,
                  "customers %d [%lld,%lld] and %d [%lld,%lld] overlap in room %d",
                  prev + 1, intervals[prev].first, intervals[prev].second,
                  cur + 1, intervals[cur].first, intervals[cur].second,
                  r);
        }
    }
}

if (!ouf.seekEof())
    quitf(_wa, "extra information in the output file");

quitf(_ok, "valid allocation with %d rooms", k);

}
