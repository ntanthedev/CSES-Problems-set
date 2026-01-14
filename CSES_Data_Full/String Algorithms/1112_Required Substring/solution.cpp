#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int step[101][128];
ll ways[1001][101];

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int m = s.size();

    for (int i = 0; i < m; i++) {
        for (int c = 'A'; c <= 'Z'; c++) {
            string u = s.substr(0, i) + (char)c;
            while (s.substr(0, u.size()) != u) {
                u = u.substr(1);
            }
            step[i][c] = u.size();
        }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
        step[m][c] = m;
    }

    ways[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 'A'; c <= 'Z'; c++) {
                ways[i + 1][step[j][c]] += ways[i][j];
                ways[i + 1][step[j][c]] %= M;
            }
        }
    }

    cout << ways[n][m] << '\n';
}
