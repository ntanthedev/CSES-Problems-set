# 1141 - Playlist

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một danh sách phát của một đài phát thanh từ khi thành lập. Danh sách phát có tổng cộng $n$ bài hát.

Hỏi độ dài của đoạn gồm các bài hát liên tiếp dài nhất mà mỗi bài hát là duy nhất là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng bài hát.

Dòng tiếp theo chứa $n$ số nguyên $k\_1,k\_2,\ldots,k\_n$: mã số của mỗi bài hát.

# Kết quả

In ra độ dài của đoạn dài nhất gồm các bài hát duy nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le k\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8
1 2 1 3 2 7 4 2
```

Kết quả:

```cpp
5
```
