# 1202 - Investigation

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn sẽ đi từ Syrjälä đến Lehmälä bằng máy bay. Bạn muốn tìm câu trả lời cho các câu hỏi sau:

* giá rẻ nhất của một đường đi như vậy là bao nhiêu?
* có bao nhiêu đường đi với giá rẻ nhất? (modulo $10^9+7$)
* số chuyến bay ít nhất trong một đường đi giá rẻ nhất là bao nhiêu?
* số chuyến bay nhiều nhất trong một đường đi giá rẻ nhất là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số lượng chuyến bay. Các thành phố được đánh số $1,2,\ldots,n$. Thành phố 1 là Syrjälä, và thành phố $n$ là Lehmälä.

Sau đó, có $m$ dòng mô tả các chuyến bay. Mỗi dòng chứa ba số nguyên $a$, $b$, và $c$: có một chuyến bay từ thành phố $a$ đến thành phố $b$ với giá $c$. Tất cả các chuyến bay đều là một chiều.

Bạn có thể giả sử rằng luôn có đường đi từ Syrjälä đến Lehmälä.

# Kết quả

In ra bốn số nguyên theo yêu cầu của đề bài.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Input:

```cpp
4 5
1 4 5
1 2 4
2 4 5
1 3 2
3 4 3
```

Output:

```cpp
5 2 1 2
```
