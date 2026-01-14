#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> wishes(n);
    for (int i = 0; i < n; i++) {
        cin >> wishes[i];
    }
    sort(wishes.begin(), wishes.end());

    vector<int> sizes(m);
    for (int i = 0; i < m; i++) {
        cin >> sizes[i];
    }
    sort(sizes.begin(), sizes.end());

    int count = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < m && sizes[j] < wishes[i] - k) {
            j++;
        }
        if (j < m && sizes[j] <= wishes[i] + k) {
            count++;
            j++;
        }
    }
    cout << count << "\n";
}
