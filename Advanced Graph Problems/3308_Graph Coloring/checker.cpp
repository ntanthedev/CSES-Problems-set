#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        adj[a][b] = adj[b][a] = true;
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d colors but optimal is %d", k, k_ans);
    if (k < 1 || k > n)
        quitf(_wa, "Number of colors %d out of range [1,%d]", k, n);

    vector<int> col(n + 1);
    for (int i = 1; i <= n; i++) {
        col[i] = ouf.readInt();
        if (col[i] < 1 || col[i] > k)
            quitf(_wa, "Node %d has color %d (must be 1..%d)", i, col[i], k);
    }

    for (int i = 1; i <= n; i++)
        ans.readInt();

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (adj[i][j] && col[i] == col[j])
                quitf(_wa, "Edge %d-%d connects nodes of same color %d", i, j, col[i]);
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal coloring with %d colors", k);
}
