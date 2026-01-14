# 1141 - Playlist

We go through the list of songs and calculate the length of the longest sequence that ends at each position.

Since we want that every song in the sequence is unique, we also store the last position we have seen each song. Using this information we can maintain the left boundary for the sequence.

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> last;
    int left = 0;
    int best = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        left = max(left, last[x]);
        best = max(best, i - left);
        last[x] = i;
    }
    cout << best << "\n";
}
```