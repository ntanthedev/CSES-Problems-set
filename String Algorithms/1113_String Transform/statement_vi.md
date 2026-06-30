# 1113 - Biến đổi xâu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét phép biến đổi xâu sau đây:

1. thêm ký tự # vào xâu (ta giả sử # nhỏ hơn về mặt từ điển so với tất cả các ký tự khác của xâu)
2. sinh ra tất cả các phép xoay của xâu
3. sắp xếp các phép xoay theo thứ tự tăng dần
4. dựa trên thứ tự này, xây dựng một xâu mới chứa ký tự cuối cùng của mỗi phép xoay

Ví dụ, xâu `babc` trở thành `babc#`. Sau đó, danh sách đã sắp xếp các phép xoay là `#babc`, `abc#b`, `babc#`, `bc#ba`, và `c#bab`. Điều này tạo ra xâu `cb#ab`.

# Dữ liệu vào

Dòng duy nhất chứa xâu đã biến đổi có độ dài $n+1$. Mỗi ký tự của xâu ban đầu là một trong các chữ a–z.

# Kết quả

In ra xâu ban đầu có độ dài $n$.

# Giới hạn

* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
cb#ab
```

Kết quả:

```cpp
babc
```
