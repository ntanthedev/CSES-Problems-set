# 2137 - Đếm ô lưới góc

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới $n \times n$ mà mỗi ô có màu đen hoặc trắng. Một ô lưới con được gọi là *đẹp* nếu chiều cao và chiều rộng của nó ít nhất bằng hai và tất cả các góc của nó đều có màu đen. Hãy đếm số lượng ô lưới con đẹp trong lưới đã cho.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của lưới.

Sau đó là $n$ dòng mô tả lưới: `1` nghĩa là ô màu đen và `0` nghĩa là ô màu trắng.

# Kết quả

In ra số lượng ô lưới con đẹp.

# Giới hạn

* $1 \le n \le 3000$

# Ví dụ

Dữ liệu vào:

```cpp
5
00010
11111
00110
11001
00010
```

Kết quả:

```cpp
4
```
