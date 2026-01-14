#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> order[i];
    }

    vector<int> max_count(n + 1);

    for (int i = 1; i <= n; i++) {
        if (order[i] == 0) {
            continue;
        }

        int pos = i;
        int length = 0;
        do {
            length++;
            int new_pos = order[pos];
            order[pos] = 0;
            pos = new_pos;
        } while (pos != i);

        for (int x = 2; x * x <= length; x++) {
            int count = 0;
            while (length % x == 0) {
                length /= x;
                count++;
            }
            max_count[x] = max(max_count[x], count);
        }
        if (!max_count[length]) {
            max_count[length] = 1;
        }
    }

    ll result = 1;
    for (int x = 2; x <= n; x++) {
        for (int i = 0; i < max_count[x]; i++) {
            result *= x;
            result %= M;
        }
    }
    cout << result << "\n";
}
