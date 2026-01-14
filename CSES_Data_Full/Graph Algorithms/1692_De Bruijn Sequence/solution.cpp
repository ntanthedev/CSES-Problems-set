#include <iostream>
#include <vector>
using namespace std;

vector<int> result;
vector<int> seen;

void search(int pos, int part, int n) {
    if (pos == (1 << n) + n - 1) {
        for (int i = 0; i < pos; i++) {
            cout << result[i];
        }
        cout << "\n";
        exit(0);
    }

    part = (part << 1) & ((1 << n) - 1);

    for (int i = 0; i < 2; i++) {
        if (!seen[part]) {
            seen[part] = true;
            result[pos] = i;
            search(pos + 1, part, n);
            seen[part] = false;
        }
        part++;
    }
}

int main() {
    int n;
    cin >> n;

    seen.resize(1 << n);
    seen[0] = true;

    result.resize((1 << n) + n - 1);
    search(n, 0, n);
}
