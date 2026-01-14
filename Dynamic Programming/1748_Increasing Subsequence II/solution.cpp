#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int M = 1000000007;
const int N = 1 << 18;
int tree[2 * N];

void inc_val(int pos, int value) {
    pos += N;
    tree[pos] = (tree[pos] + value) % M;
    for (pos /= 2; pos >= 1; pos /= 2) {
        tree[pos] = (tree[pos * 2] + tree[pos * 2 + 1]) % M;
    }
}

int find_sum(int a, int b) {
    a += N;
    b += N;
    int sum = 0;
    while (a <= b) {
        if (a % 2 == 1) sum = (sum + tree[a++]) % M;
        if (b % 2 == 0) sum = (sum + tree[b--]) % M;
        a /= 2;
        b /= 2;
    }
    return sum;
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; i++) {
        cin >> pairs[i].first;
        pairs[i].second = i;
    }
    sort(pairs.begin(), pairs.end());

    vector<int> values(n);
    int new_value = 1;
    for (int i = 0; i < n; i++) {
        if (i != 0 && pairs[i - 1].first != pairs[i].first) {
            new_value++;
        }
        values[pairs[i].second] = new_value;
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
        int result = find_sum(0, values[i] - 1) + 1;
        inc_val(values[i], result);
        total = (total + result) % M;
    }
    cout << total << "\n";
}
