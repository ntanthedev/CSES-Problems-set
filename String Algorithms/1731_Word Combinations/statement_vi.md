# 1731 - Tổ hợp từ

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu có độ dài $n$ và một từ điển chứa $k$ từ. Có bao nhiêu cách để tạo ra xâu đó bằng các từ trong từ điển?

# Dữ liệu vào

Dòng đầu tiên chứa một xâu gồm $n$ ký tự từ a–z.

Dòng thứ hai chứa một số nguyên $k$: số lượng từ trong từ điển.

Cuối cùng là $k$ dòng mô tả các từ. Mỗi từ là duy nhất và gồm các ký tự a–z.

# Kết quả

In ra số cách theo modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 5000$
* $1 \le k \le 10^5$
* tổng độ dài của các từ không vượt quá $10^6$

# Ví dụ

Dữ liệu vào:

```cpp
ababc
4
ab
abab
c
cb
```

Kết quả:

```cpp
2
```

Giải thích: Các cách khả dụng là `ab+ab+c` và `abab+c`.
