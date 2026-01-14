#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const int N = 100001;
const int MOD = 1000000007;
const ll INF = 1e18;

vector<pair<int, int>> g[N];
vector<pair<int, int>> rev_g[N];
ll price[N];
int n;

bool ready[N];
ll n_min_price[N];
ll min_flights[N];
ll max_flights[N];

void f(int x) {
    if (ready[x]) return;
    ready[x] = true;
    if (x == n) {
        n_min_price[x] = 1;
        min_flights[x] = 0;
        max_flights[x] = 0;
        return;
    }
    n_min_price[x] = 0;
    min_flights[x] = INF;
    max_flights[x] = -INF;
    for (auto [y, len] : g[x]) {
        if (price[x] == price[y] + len) {
            f(y);
            n_min_price[x] = (n_min_price[x] + n_min_price[y]) % MOD;
            min_flights[x] = min(min_flights[x], min_flights[y] + 1);
            max_flights[x] = max(max_flights[x], max_flights[y] + 1);
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        rev_g[b].emplace_back(a, c);
    }

    fill(price, price + n + 1, INF);

    reverse_priority_queue<pair<ll, int>> queue;
    queue.emplace(0, n);
    price[n] = 0;

    while (!queue.empty()) {
        auto [d, x] = queue.top();
        queue.pop();
        if (d > price[x]) continue;
        for (auto [y, len] : rev_g[x]) {
            ll new_d = d + len;
            if (new_d < price[y]) {
                price[y] = new_d;
                queue.emplace(new_d, y);
            }
        }
    }

    f(1);

    cout << price[1] << ' ' << n_min_price[1] << ' ';
    cout << min_flights[1] << ' ' << max_flights[1] << '\n';
}
