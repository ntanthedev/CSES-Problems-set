# 1162 - Các Phương Pháp Sắp Xếp

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Dưới đây là một số phương pháp có thể dùng để sắp xếp các phần tử của một mảng theo thứ tự tăng dần:

1. Mỗi bước, chọn hai phần tử liền kề và đổi chỗ chúng.
2. Mỗi bước, chọn hai phần tử bất kỳ và đổi chỗ chúng.
3. Mỗi bước, chọn một phần tử bất kỳ và di chuyển nó đến một vị trí khác.
4. Mỗi bước, chọn một phần tử bất kỳ và di chuyển nó lên đầu mảng.

Cho một hoán vị của các số $1,2,\ldots,n$, hãy tính số bước tối thiểu để sắp xếp mảng bằng các phương pháp trên.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$.

Dòng thứ hai chứa $n$ số nguyên mô tả hoán vị.

# Kết quả

In ra bốn số: số bước tối thiểu khi sử dụng mỗi phương pháp.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
8
7 8 2 6 5 1 3 4
```

Kết quả:

```cpp
20 6 5 6
```
