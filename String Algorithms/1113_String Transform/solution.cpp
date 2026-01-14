#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    vector<pair<char, int>> chars;
    for (int i = 0; i < n; i++) {
        chars.emplace_back(s[i], i);
    }
    sort(chars.begin(), chars.end());

    vector<int> link(n);
    for (int i = 0; i < n; i++) {
        link[chars[i].second] = i;
    }

    int pos = 0;
    string res;
    for (int i = 0; i < n - 1; i++) {
        res += s[pos];
        pos = link[pos];
    }
    reverse(res.begin(), res.end());
    cout << res << "\n";
}
