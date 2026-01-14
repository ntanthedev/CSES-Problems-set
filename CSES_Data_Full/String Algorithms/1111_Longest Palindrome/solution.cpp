#include <iostream>
#include <vector>
using namespace std;

// assumes length of s is odd
string manacher(string s) {
    int n = s.size();
    int left = 0, right = 0;
    vector<int> len(n);
    int pos = 0;
    for (int i = 0; i < n; i++) {
        int l = 1;
        if (i <= right) {
            l = min(right - i + 1, len[left + right - i]);
        }
        while (i - l >= 0 && i + l < n && s[i - l] == s[i + l]) {
            l++;
            left = i - l + 1;
            right = i + l - 1;
        }
        len[i] = l;
        if (l > len[pos]) pos = i;
    }
    return s.substr(pos - len[pos] + 1, 2 * len[pos] - 1);
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    string input = string(2 * n + 1, '*');
    for (int i = 0; i < n; i++) {
        input[2 * i + 1] = s[i];
    }
    string output = manacher(input);
    for (int i = 1; i < output.size(); i += 2) {
        cout << output[i];
    }
    cout << "\n";
}
