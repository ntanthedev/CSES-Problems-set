#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct ParentInfo {
    int pa, pb;
    string move;
};

int main() {
    int capA, capB, target;
    cin >> capA >> capB >> target;

    if (target > capA) {
        cout << "-1\n";
        return 0;
    }

    const int MAXA = 1000;
    const int MAXB = 1000;
    const int INF = 1e9;
    vector<vector<int>> dist(MAXA + 1, vector<int>(MAXB + 1, INF));
    vector<vector<ParentInfo>> parent(MAXA + 1, vector<ParentInfo>(MAXB + 1, {-1, -1, ""}));
    priority_queue<pair<int, pair<int, int>>,
                   vector<pair<int, pair<int, int>>>,
                   greater<>> pq;

    dist[0][0] = 0;
    pq.push({0, {0, 0}});

    auto relax = [&](int a, int b, int na, int nb, int add, const string& mv) {
        if (add < 1) return;
        int nd = dist[a][b] + add;
        if (nd < dist[na][nb]) {
            dist[na][nb] = nd;
            parent[na][nb] = {a, b, mv};
            pq.push({nd, {na, nb}});
        }
    };

    while (!pq.empty()) {
        auto [d, state] = pq.top();
        pq.pop();
        int a = state.first, b = state.second;
        if (d != dist[a][b]) continue;

        relax(a, b, capA, b, capA - a, "FILL A");
        relax(a, b, a, capB, capB - b, "FILL B");
        relax(a, b, 0, b, a, "EMPTY A");
        relax(a, b, a, 0, b, "EMPTY B");

        int pour = min(a, capB - b);
        relax(a, b, a - pour, b + pour, pour, "MOVE A B");
        pour = min(b, capA - a);
        relax(a, b, a + pour, b - pour, pour, "MOVE B A");
    }

    int bestB = -1, best = INF;
    for (int b = 0; b <= capB; b++) {
        if (dist[target][b] < best) {
            best = dist[target][b];
            bestB = b;
        }
    }

    if (best >= INF) {
        cout << "-1\n";
        return 0;
    }

    vector<string> moves;
    int a = target, b = bestB;
    while (!(a == 0 && b == 0)) {
        ParentInfo p = parent[a][b];
        moves.push_back(p.move);
        a = p.pa;
        b = p.pb;
    }
    reverse(moves.begin(), moves.end());

    cout << moves.size() << " " << best << "\n";
    for (const string& mv : moves) cout << mv << "\n";
}
