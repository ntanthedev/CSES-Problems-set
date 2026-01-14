#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    sort(weights.begin(), weights.end());

    int count = 0;
    int i = 0;
    int j = n - 1;
    while (i <= j) {
        if (i < j && weights[i] + weights[j] <= x) {
            count++;
            i++;
            j--;
        } else {
            count++;
            j--;
        }
    }
    cout << count << "\n";
}
