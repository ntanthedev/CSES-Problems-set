# 1111 - Palindrome dài nhất

Trước hết, ta tập trung vào việc tìm palindrome độ dài lẻ dài nhất trong một xâu. Ta duyệt qua xâu và tính giá trị $\textrm{len}[i]$ cho mỗi vị trí $i$: độ dài của palindrome độ dài lẻ dài nhất có vị trí trung tâm là $i$. Ví dụ, kết quả cho xâu `abacabac` là $[1, 2, 1, 4, 1, 3, 1, 1]$.

Ta có thể giải bài toán bằng thuật toán Manacher hoạt động hơi giống thuật toán Z. Ta ghi nhớ khoảng của một palindrome tìm được cho đến nay có đầu mút phải xa nhất có thể, và sử dụng thực tế rằng vị trí trung tâm của palindrome phản chiếu nửa trái và nửa phải của palindrome.

Trong ví dụ của ta, giả sử ta đã tính giá trị $\textrm{len}[3]=4$ tương ứng với palindrome `abacaba` có khoảng $[0,6]$. Khi ta muốn tính giá trị $\textrm{len}[5]$, ta biết ngay rằng nó phải có ít nhất $\textrm{len}[1]=2$, bởi vì vị trí $5$ nằm trong khoảng $[0,6]$ và vị trí trung tâm $3$ phản chiếu các vị trí $1$ và $5$. Sau đó, ta mở rộng palindrome ra ngoài đầu mút phải và khám phá ra rằng $\textrm{len}[5]=3$ tương ứng với palindrome `cabac` có khoảng $[3,7]$.

Thuật toán hoạt động trong $O(n)$ thời gian vì ta chỉ so sánh các ký tự nằm ngoài đầu mút phải, và sau đó di chuyển đầu mút nếu các ký tự khớp nhau. Tổng số bước mà đầu mút phải di chuyển là $O(n)$.

Cuối cùng, để cũng tìm các palindrome độ dài chẵn, ta sửa đổi đầu vào một chút bằng cách thêm một ký tự đặc biệt `*` vào giữa mỗi ký tự và ở cả hai đầu. Ví dụ, xâu `abacabac` trở thành `*a*b*a*c*a*b*a*c*`. Sử dụng thủ thuật này, mọi palindrome đều là palindrome độ dài lẻ và ta có thể tìm thấy tất cả chúng.

```cpp
#include <iostream>
#include <vector>
using namespace std;

// giả sử độ dài của s là lẻ
string manacher(string s) {
    int n = s.size();
    int left = 0, right = 0;
    vector<int> len(n);
    int pos = 0;
    for (int i = 0; i < n; i++) {
        int l = 1;
        if (i <= right) {
            l = min(right - i + 1, len[left + right - i]);
        }
        while (i - l >= 0 && i + l < n && s[i - l] == s[i + l]) {
            l++;
            left = i - l + 1;
            right = i + l - 1;
        }
        len[i] = l;
        if (l > len[pos]) pos = i;
    }
    return s.substr(pos - len[pos] + 1, 2 * len[pos] - 1);
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    string input = string(2 * n + 1, '*');
    for (int i = 0; i < n; i++) {
        input[2 * i + 1] = s[i];
    }
    string output = manacher(input);
    for (int i = 1; i < output.size(); i += 2) {
        cout << output[i];
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [Longest palindromic substring (Wikipedia)](https://en.wikipedia.org/wiki/Longest_palindromic_substring)
* Manacher, G.: A new linear-time "on-line" algorithm for finding the smallest initial palindrome of a string. Journal of the ACM, 22(3), 346–351 (1975)
