# 3304 - Visible Buildings Queries

We first find the index of the next higher building for each building (or $\infty$ if there is no such building). This is done in linear time using a stack.

After that, we create a jump array that, for each building, indicates the next higher building to the right after $x$ steps where $x$ is a power of two. Since there are $O(\log n)$ possible powers of two, creating the array takes $O(n \log n)$ time.

Finally, we can answer any query in $O(\log n)$ time using the jump array.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 17;
const int INF = 1000000001;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> heights(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> heights[i];
    }
    heights[n + 1] = INF;

    vector<vector<int>> jump(N, vector<int>(n + 2));
    jump[0][n + 1] = n + 1;

    vector<int> stack;
    stack.push_back(n + 1);
    for (int i = n; i >= 1; i--) {
        while (heights[stack.back()] <= heights[i]) {
            stack.pop_back();
        }
        jump[0][i] = stack.back();
        stack.push_back(i);
    }

    for (int k = 1; k < N; k++) {
        for (int i = 1; i <= n + 1; i++) {
            jump[k][i] = jump[k - 1][jump[k - 1][i]];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        int pos = a;
        int answer = 1;
        for (int k = N - 1; k >= 0; k--) {
            if (jump[k][pos] <= b) {
                answer += 1 << k;
                pos = jump[k][pos];
            }
        }
        cout << answer << "\n";
    }
}
```