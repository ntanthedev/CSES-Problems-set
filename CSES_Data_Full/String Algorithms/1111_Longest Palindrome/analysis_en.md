# 1111 - Longest Palindrome

Let us first focus on finding the longest odd-length palindrome in a string. We go through the string and calculate a value $\textrm{len}[i]$ for each position $i$: the length of the longest odd-length palindrome whose middle position is $i$. For example, the result for the string `abacabac` is $[1, 2, 1, 4, 1, 3, 1, 1]$.

We can solve the problem using Manacher's algorithm that works a bit like the Z-algorithm. We remember the range of a palindrome found so far whose right endpoint is as far as possible, and use the fact that the middle position of the palindrome mirrors the left and right side of the palindrome.

In our example, suppose that we have calculated the value $\textrm{len}[3]=4$ that corresponds to the palindrome `abacaba` whose range is $[0,6]$. When we later want to calculate the value $\textrm{len}[5]$, we immediately know that it has to be at least $\textrm{len}[1]=2$, because the position $5$ is in the range $[0,6]$ and the middle position $3$ mirrors the positions $1$ and $5$. After that, we extend the palindrome beyond the right endpoint and discover that $\textrm{len}[5]=3$ which corresponds to the palindrome `cabac` whose range is $[3,7]$.

The algorithm works in $O(n)$ time because we only compare characters that are beyond the right endpoint, and then move the endpoint if the characters match. The total number of steps the right endpoint moves is $O(n)$.

Finally, to also find even-length palindromes, we modify the input a bit by adding a special character `*` between each character and to both ends. For example, the string `abacabac` becomes `*a*b*a*c*a*b*a*c*`. Using this trick, every palindrome is an odd-length palindrome and we can find them all.

```cpp
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
```

## References

* [Longest palindromic substring (Wikipedia)](https://en.wikipedia.org/wiki/Longest_palindromic_substring)
* Manacher, G.: A new linear-time "on-line" algorithm for finding the smallest initial palindrome of a string. Journal of the ACM, 22(3), 346–351 (1975)