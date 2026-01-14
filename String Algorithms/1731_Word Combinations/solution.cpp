#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1000000;
const int M = 1000000007;

int trie[N + 1][26];
int trie_pos;
bool final[N + 1];

int main() {
    string s;
    cin >> s;
    int n = s.size();

    int k;
    cin >> k;
    while (k--) {
        string w;
        cin >> w;
        int node = 0;
        for (auto c : w) {
            int idx = c - 'a';
            if (trie[node][idx] == 0) {
                trie[node][idx] = ++trie_pos;
            }
            node = trie[node][idx];
        }
        final[node] = true;
    }

    vector<ll> ways(n + 1);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        ways[i] = 0;
        int node = 0;
        for (int j = i; j < n; j++) {
            node = trie[node][s[j] - 'a'];
            if (node == 0) break;
            if (final[node]) {
                ways[i] += ways[j + 1];
                ways[i] %= M;
            }
        }
    }

    cout << ways[0] << "\n";
}
