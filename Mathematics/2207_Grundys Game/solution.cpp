#include <iostream>
#include <set>
using namespace std;
const int N = 1000000;
int grundy[N + 1];

int main() {
    for (int i = 1; i <= N; i++) {
        set<int> s;
        for (int j = 1; i - j > j; j++) {
            s.insert(grundy[j] ^ grundy[i - j]);
        }
        grundy[i] = 0;
        while (s.count(grundy[i])) {
            grundy[i]++;
        }
    }

    int t;
    cin >> t;
    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        cout << (grundy[n] ? "first" : "second") << "\n";
    }
}
