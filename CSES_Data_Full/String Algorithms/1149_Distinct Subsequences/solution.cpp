#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (int i = 0; i < n; i++) {
        int sum = 1;
        for (int c = 'a'; c <= 'z'; c++) {
            sum += count[c];
            sum %= M;
        }
        count[s[i]] = sum;
    }

    ll ans = 0;
    for (int c = 'a'; c <= 'z'; c++) {
        ans += count[c];
        ans %= M;
    }

    cout << ans << "\n";
}
