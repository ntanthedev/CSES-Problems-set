#include <iostream>
#include <vector>

using namespace std;

const int N = 100001;
const int INF = 1000000000;
vector<int> g[N];

bool ready[N];
int longest[N];
int next_city[N];
int n;

int f(int x) {
    if (ready[x]) return longest[x];
    ready[x] = true;
    longest[x] = -INF;
    if (x == n) {
        return longest[x] = 1;
    }
    for (int y : g[x]) {
        f(y);
        if (longest[y] + 1 > longest[x]) {
            longest[x] = longest[y] + 1;
            next_city[x] = y;
        }
    }
    return longest[x];
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    if (f(1) < 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << f(1) << '\n';
    int x = 1;
    while (x != 0) {
        cout << x << ' ';
        x = next_city[x];
    }
    cout << '\n';
}
