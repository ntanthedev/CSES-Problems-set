# 3422 - Hoán vị thứ ba

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho hai hoán vị $a$ và $b$ sao cho $a\_i \neq b\_i$ tại mọi vị trí. Hãy tạo một hoán vị thứ ba $c$ sao cho $a\_i \neq c\_i$ và $b\_i \neq c\_i$ tại mọi vị trí.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước hoán vị.

Dòng thứ hai chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$.

Dòng thứ ba chứa $n$ số nguyên $b\_1,b\_2,\dots,b\_n$.

# Kết quả

In ra $n$ số nguyên $c\_1,c\_2,\dots,c\_n$. Bạn có thể in ra bất kỳ phương án hợp lệ nào. Nếu không có lời giải, in ra `IMPOSSIBLE`.

# Giới hạn

* $2 \le n \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 3 2 5 4
4 1 3 2 5
```

Kết quả:

```cpp
3 2 5 4 1
```
