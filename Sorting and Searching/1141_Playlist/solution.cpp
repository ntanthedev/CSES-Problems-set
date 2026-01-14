#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> last;
    int left = 0;
    int best = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        left = max(left, last[x]);
        best = max(best, i - left);
        last[x] = i;
    }
    cout << best << "\n";
}
