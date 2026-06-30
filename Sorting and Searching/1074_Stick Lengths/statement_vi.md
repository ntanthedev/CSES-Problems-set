# 1074 - Stick Lengths

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ que với một số độ dài. Nhiệm vụ của bạn là biến đổi các que sao cho mỗi que có cùng độ dài.

Bạn có thể kéo dài hoặc cắt ngắn mỗi que. Cả hai thao tác đều có chi phí là $x$ với $x$ là độ chênh lệch giữa độ dài mới và độ dài ban đầu.

Hỏi tổng chi phí tối thiểu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng que.

Sau đó là $n$ số nguyên: $p\_1,p\_2,\ldots,p\_n$: độ dài của các que.

# Kết quả

In ra một số nguyên: tổng chi phí tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le p\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 3 1 5 2
```

Kết quả:

```cpp
5
```
