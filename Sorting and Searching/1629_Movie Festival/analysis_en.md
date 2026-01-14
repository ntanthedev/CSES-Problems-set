# 1629 - Movie Festival

An optimal solution is to always choose a movie that starts after the last movie we watched and has the earliest ending time among all such movies. This can be done by sorting the movies by ending time, after which we can go through them and greedily choose the next movie.

The algorithm works because it is always safe to choose the next movie that has the earliest ending time. If we chose some other movie, it would end later and restrict more our future choices.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> movies;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        movies.emplace_back(b, a);
    }
    sort(movies.begin(), movies.end());

    int count = 0;
    int end = 0;
    for (auto [b, a] : movies) {
        if (a >= end) {
            end = b;
            count++;
        }
    }
    cout << count << "\n";
}
```