# 2207 - Trò chơi Grundy

## Solution 1

Gọi $\textrm{grundy}[x]$ là số Grundy của một đống có $x$ đồng xu, và gọi $\oplus$
là phép toán xor.

Khi ta chia một đống $x$ đồng xu thành hai đống $a$ và $b$ đồng xu, sẽ có hai
trò chơi con có số Grundy lần lượt là $\textrm{grundy}[a]$ và
$\textrm{grundy}[b]$, do đó số Grundy sau nước đi là
$\textrm{grundy}[a] \oplus \textrm{grundy}[b]$.

Để tính $\textrm{grundy}[x]$, ta duyệt qua mọi cách chia một đống $x$ đồng xu
thành hai đống, tính số Grundy của mỗi nước đi và tìm giá trị mex của chúng, tức
là số nguyên không âm nhỏ nhất không xuất hiện trong các số đó.

Lời giải này hoạt động nhưng quá chậm vì nó có độ phức tạp bình phương và $N$ có
thể lên đến $10^6$. Tuy nhiên, ta có thể nghiên cứu bài toán bằng lời giải này.

```cpp
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
```

## Solution 2

Bằng cách nghiên cứu lời giải thứ nhất, ta có thể nhận thấy $1222$ là trạng thái
cuối cùng có số Grundy bằng 0, tức là ta đang ở thế thua. Do đó, chỉ cần tính số
Grundy của các trạng thái $0 \dots 1222$ là đủ vì ta luôn thắng nếu có nhiều hơn
$1222$ đồng xu.

Lưu ý rằng việc tìm kiếm của ta chỉ chứng minh $1222$ là thế thua cuối cùng trong
các trạng thái $0 \dots 10^6$. Tuy nhiên, người ta biết rằng điều này cũng đúng
cho các trạng thái $0 \dots 2^{35}$. Không ai biết liệu có thế thua nào sau đó
hay không.

```cpp
#include <iostream>
#include <set>
using namespace std;
const int N = 1222;
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
        bool win = n > N || grundy[n];
        cout << (win ? "first" : "second") << "\n";
    }
}
```

## Tài liệu tham khảo

* [Grundy's game (Wikipedia)](https://en.wikipedia.org/wiki/Grundy%27s_game)
* [A. Flammenkamp: Sprague-Grundy values of Grundy's game](https://wwwhomes.uni-bielefeld.de/achim/grundy.html)
