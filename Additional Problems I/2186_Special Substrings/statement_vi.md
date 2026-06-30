# 2186 - Xâu Con Đặc Biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một xâu con được gọi là *đặc biệt* nếu mọi ký tự xuất hiện trong xâu đều xuất hiện cùng số lần trong xâu con đó.

Nhiệm vụ của bạn là đếm số lượng xâu con đặc biệt trong một xâu cho trước.

# Dữ liệu vào

Dòng đầu vào duy nhất chứa một xâu có độ dài $n$. Mỗi ký tự nằm trong khoảng a...z.

# Kết quả

In ra một số nguyên: số lượng xâu con đặc biệt.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
abccabab
```

Kết quả:

```cpp
5
```

*Giải thích*: Các xâu con đặc biệt là `abc`, `cab`, `abccab`, `bccaba` và `ccabab`.
