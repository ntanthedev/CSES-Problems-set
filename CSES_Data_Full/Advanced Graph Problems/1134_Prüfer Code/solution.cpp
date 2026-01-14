#include <iostream>
#include <queue>
using namespace std;

const int N = 200001;
int code[N];
int degree[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n - 2; ++i) {
        cin >> code[i];
        degree[code[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 0) {
            leaves.push(i);
        }
    }

    for (int i = 1; i <= n - 2; ++i) {
        cout << code[i] << ' ' << leaves.top() << '\n';
        leaves.pop();
        degree[code[i]]--;
        if (degree[code[i]] == 0) {
            leaves.push(code[i]);
        }
    }

    cout << leaves.top() << ' ' << n << endl;
}
