#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1 << 18;

vector<int> tree[2 * N];

int query(int a, int b, int c, int d) {
    a += N;
    b += N;

    int count = 0;

    while (a <= b) {
        if (a % 2 == 1) {
            count += upper_bound(tree[a].begin(), tree[a].end(), d) -
                     lower_bound(tree[a].begin(), tree[a].end(), c);
            a++;
        }
        if (b % 2 == 0) {
            count += upper_bound(tree[b].begin(), tree[b].end(), d) -
                     lower_bound(tree[b].begin(), tree[b].end(), c);
            b--;
        }
        a /= 2;
        b /= 2;
    }

    return count;
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tree[N + i] = {x};
    }

    for (int i = N - 1; i >= 1; i--) {
        merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(),
              tree[2 * i + 1].end(), back_inserter(tree[i]));
    }

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        cout << query(a, b, c, d) << "\n";
    }
}
