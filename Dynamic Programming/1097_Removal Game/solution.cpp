#include <iostream>
using namespace std;
using ll = long long;

const int N = 5000;
int x[N];
ll score[N];

int main() {
    int n;
    cin >> n;

    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        score[i] = x[i];
        sum += x[i];
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len - 1;
            score[l] = max(x[l] - score[l + 1], x[r] - score[l]);
        }
    }

    cout << (sum + score[0]) / 2 << endl;
}
