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
    string s;
    cin >> s;
    int n = s.size();

    auto z = z_algo(s);
    for (int i = n - 1; i > 0; i--) {
        if (z[i] == n - i) {
            cout << n - i << " ";
        }
    }
    cout << "\n";
}
