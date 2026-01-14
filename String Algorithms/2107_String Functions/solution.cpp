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

    vector<int> z = z_algo(s);

    vector<int> p(n);
    for (int i = n - 1; i > 0; i--) {
        p[i + z[i] - 1] = z[i];
    }
    for (int i = n - 2; i > 0; i--) {
        p[i] = max(p[i], p[i + 1] - 1);
    }

    for (auto x : z) {
        cout << x << " ";
    }
    cout << "\n";

    for (auto x : p) {
        cout << x << " ";
    }
    cout << "\n";
}
