#include <iostream>
#include <vector>
using namespace std;

// finds odd-length palindromes
vector<int> manacher(string s) {
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
    return len;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    string input(2 * n + 1, '*');
    for (int i = 0; i < n; i++) {
        input[2 * i + 1] = s[i];
    }

    auto output = manacher(input);

    vector<int> right(n);
    for (int i = 1; i < 2 * n; i++) {
        int len = output[i] - 1;
        int pos = i / 2 + len / 2;
        if (i % 2 == 0) pos--;
        right[pos] = max(right[pos], len);
    }

    vector<int> result(n, 1);

    int max_length = 0;
    for (int i = n - 1; i >= 0; i--) {
        max_length = max(max_length, right[i]);
        result[i] = max_length;
        max_length -= 2;
    }

    for (int i = 0; i < n; i++) {
        cout << result[i];
        if (i != n - 1) cout << " ";
    }
    cout << "\n";
}
