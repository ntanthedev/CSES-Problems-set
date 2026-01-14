#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (s.substr(pos, n) > s.substr(i, n)) {
            pos = i;
        }
    }
    cout << s.substr(pos, n) << "\n";
}
