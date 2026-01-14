#include <iostream>
#include <vector>

using namespace std;

const int N = 100001;
const int MOD = 1000000007;

vector<int> g[N];

bool ready[N];
int n_ways[N];
int n;

int f(int x) {
    if (ready[x]) return n_ways[x];
    ready[x] = true;
    if (x == n) {
        return n_ways[x] = 1;
    }
    for (int y : g[x]) {
        n_ways[x] = (n_ways[x] + f(y)) % MOD;
    }
    return n_ways[x];
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    cout << f(1) << endl;
}
