#include <iostream>
#include <vector>
using namespace std;

vector<int> z_algo(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    string s, p;
    cin >> s;
    int n = s.size();
    cin >> p;
    int m = p.size();

    string t = p + "$" + s;
    auto z = z_algo(t);
    int count = 0;
    for (int i = 0; i < n + m + 1; i++) {
        if (z[i] == m) count++;
    }
    cout << count << "\n";
}
