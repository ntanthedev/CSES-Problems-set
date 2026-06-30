# 1731 - Tổ hợp từ

## Lời giải 1 (trie)

Ta tạo một trie chứa tất cả các từ trong từ điển. Nút gốc của
trie có chỉ số $0$, và `trie`$[i][x]$ trỏ đến một nút ta sẽ di chuyển từ nút
$i$ sau khi đọc ký tự $x$. Ngoài ra, `final`$[i]$ là true nếu một từ nào đó
kết thúc tại nút $i$.

Ta sử dụng quy hoạch động để đếm các tổ hợp. Ta tạo một mảng `ways`
lưu, với mỗi hậu tố của xâu, số cách để tạo hậu tố đó bằng từ điển.
Ta duyệt qua từng tiền tố của hậu tố và đi theo các liên kết trong trie
để tìm các tiền tố nằm trong từ điển.

Thuật toán hoạt động trong $O(n^2+N)$ thời gian với $N$ là tổng độ dài của
các từ trong từ điển.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1000000;
const int M = 1000000007;

int trie[N + 1][26];
int trie_pos;
bool final[N + 1];

int main() {
    string s;
    cin >> s;
    int n = s.size();

    int k;
    cin >> k;
    while (k--) {
        string w;
        cin >> w;
        int node = 0;
        for (auto c : w) {
            int idx = c - 'a';
            if (trie[node][idx] == 0) {
                trie[node][idx] = ++trie_pos;
            }
            node = trie[node][idx];
        }
        final[node] = true;
    }

    vector<ll> ways(n + 1);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        ways[i] = 0;
        int node = 0;
        for (int j = i; j < n; j++) {
            node = trie[node][s[j] - 'a'];
            if (node == 0) break;
            if (final[node]) {
                ways[i] += ways[j + 1];
                ways[i] %= M;
            }
        }
    }

    cout << ways[0] << "\n";
}
```

## Lời giải 2 (băm)

Ta tạo một tập `hashes` chứa tất cả các băm của các từ trong
từ điển. Sau đó, ta có thể sử dụng quy hoạch động để tính đáp số như trong
lời giải trước và sử dụng tập để kiểm tra một xâu con có thuộc
từ điển hay không.

Vì ta so sánh mỗi xâu con với tất cả các từ, ta cần giá trị băm 64-bit để
đảm bảo không có va chạm, do nghịch lý ngày sinh.

Để lời giải hiệu quả hơn, ta sử dụng một thủ thuật bổ sung: ta tạo một
vector `lengths` để kiểm tra xem từ điển có chứa ít nhất
một từ có độ dài cho trước hay không. Sử dụng vector này, ta không phải kiểm
tra một xâu con có xuất hiện trong từ điển hay không nếu ta biết rằng không
có từ nào có độ dài đó trong từ điển. Vì tổng độ dài của các từ không vượt quá
$10^6$, sẽ chỉ có khoảng $\sqrt{2 \cdot 10^6} \approx 1414$ độ dài từ
phân biệt, so với $5000$ độ dài xâu con khả dụng.

Lời giải hoạt động trong $O((n^2+k) C+N)$ thời gian với $C$ là thời gian cần
cho các thao tác trên tập và $N$ là tổng độ dài của các từ.

```cpp
#include <chrono>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;

const int M = 1000000007;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll Z = 1111111111111111111;  // Z là một số nguyên tố.
const ll C = uniform_int_distribution<ll>(Z / 10, Z / 10 * 9)(rng);

struct HashString {
    ll mul(ll a, ll b) { return __int128(a) * b % Z; }

    int n;
    vector<ll> pows, sums;

    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = mul(pows[i - 1], C);
            sums[i] = (mul(sums[i - 1], C) + s[i - 1]) % Z;
        }
    }

    // Trả về băm của xâu con [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - mul(sums[l], pows[r - l]);
        return (h % Z + Z) % Z;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    HashString hs(s);
    int k;
    cin >> k;

    unordered_set<ll> hashes;
    vector<bool> lengths(n + 1);
    for (int i = 1; i <= k; i++) {
        string w;
        cin >> w;
        HashString hw(w);
        hashes.insert(hw.hash(0, w.size()));
        lengths[w.size()] = true;
    }

    vector<ll> ways(n + 1);
    ways[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (lengths[j - i] && hashes.count(hs.hash(i, j))) {
                ways[i] += ways[j];
                ways[i] %= M;
            }
        }
    }

    cout << ways[0] << "\n";
}
```
