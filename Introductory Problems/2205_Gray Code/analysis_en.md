# 2205 - Gray Code

One way to create a Gray code of length $n$ is to use recursion. Suppose that we already have a list of strings which is a Gray code of length $n-1$. Using that list, we can create a Gray code of length $n$ as follows:

* Go through the list and, for each string $s$, add a string $0s$ to the code.
* Reverse the list.
* Go through the list and, for each string $s$, add a string $1s$ to the code.

For example, given a Gray code $[00, 01, 11, 10]$ of length $2$, we can create a Gray code $[000, 001, 011, 010, 110, 111, 101, 100]$ of length $3$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<string> create(int n) {
    if (n == 1) {
        return {"0", "1"};
    }
    vector<string> code;
    auto prev = create(n - 1);
    for (auto s : prev) {
        code.push_back("0" + s);
    }
    reverse(prev.begin(), prev.end());
    for (auto s : prev) {
        code.push_back("1" + s);
    }
    return code;
}

int main() {
    int n;
    cin >> n;
    auto code = create(n);
    for (auto s : code) {
        cout << s << "\n";
    }
}
```

## References

* [Gray code (Wikipedia)](https://en.wikipedia.org/wiki/Gray_code)