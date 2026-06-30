# 1140 - Projects

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ dự án bạn có thể tham gia. Với mỗi dự án, bạn biết ngày bắt đầu và ngày kết thúc cùng với số tiền thưởng bạn sẽ nhận được. Bạn chỉ có thể tham gia một dự án trong một ngày.

Hỏi số tiền tối đa bạn có thể kiếm được là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng dự án.

Sau đó là $n$ dòng. Mỗi dòng chứa ba số nguyên $a\_i$, $b\_i$, và $p\_i$: ngày bắt đầu, ngày kết thúc và tiền thưởng.

# Kết quả

In ra một số nguyên: số tiền tối đa bạn có thể kiếm được.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a\_i \le b\_i \le 10^9$
* $1 \le p\_i \le 10^9$

# Ví dụ

Input:

```cpp
4
2 4 4
3 6 6
6 8 2
5 7 3
```

Output:

```cpp
7
```
