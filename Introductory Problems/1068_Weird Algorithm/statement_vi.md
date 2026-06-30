# 1068 - Thuật toán kỳ lạ

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một thuật toán nhận đầu vào là một số nguyên dương $n$. Nếu $n$ chẵn, thuật toán chia nó cho hai, và nếu $n$ lẻ, thuật toán nhân nó với ba rồi cộng một. Thuật toán lặp lại điều này cho đến khi $n$ bằng một. Ví dụ, dãy số với $n=3$ như sau:
$$3 \rightarrow 10 \rightarrow 5 \rightarrow 16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1$$
Nhiệm vụ của bạn là mô phỏng quá trình thực thi của thuật toán với một giá trị $n$ cho trước.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$.

# Kết quả

In ra một dòng chứa tất cả các giá trị của $n$ trong quá trình thực hiện thuật toán.

# Giới hạn

* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3
```

Kết quả:

```cpp
3 10 5 16 8 4 2 1
```