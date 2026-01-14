#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    map<int, int> last_pos;
    int left_pos = 1;
    ll count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        left_pos = max(left_pos, last_pos[x] + 1);
        count += i - left_pos + 1;
        last_pos[x] = i;
    }

    cout << count << "\n";
}
