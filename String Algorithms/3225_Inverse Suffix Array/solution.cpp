#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> suffix_array(n + 1);
    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> suffix_array[i];
        order[suffix_array[i]] = i;
    }

    auto next_rank = [&](int pos) {
        if (pos >= n) return 0;
        return order[pos + 1];
    };

    vector<char> result(n + 1);
    result[suffix_array[1]] = 'a';
    char current_char = 'a';
    for (int i = 2; i <= n; i++) {
        if (next_rank(suffix_array[i - 1]) > next_rank(suffix_array[i])) {
            current_char++;
        }
        if (current_char > 'z') {
            cout << "-1\n";
            return 0;
        }
        result[suffix_array[i]] = current_char;
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i];
    }
    cout << "\n";
}
