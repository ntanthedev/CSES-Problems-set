# 1112 - Xâu con bắt buộc

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là đếm số lượng xâu có độ dài $n$ chứa một mẫu cho trước có độ dài $m$ làm xâu con của chúng. Tất cả các xâu đều gồm các ký tự A–Z.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: độ dài của xâu cuối cùng.

Dòng thứ hai chứa một mẫu có độ dài $m$.

# Kết quả

In ra số lượng xâu theo modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 1000$
* $1 \le m \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
6
ABCDB
```

Kết quả:

```cpp
52
```

Giải thích: Xâu cuối cùng sẽ có dạng ABCDB$x$ hoặc $x$ABCDB với $x$ là bất kỳ ký tự nào từ A đến Z.
