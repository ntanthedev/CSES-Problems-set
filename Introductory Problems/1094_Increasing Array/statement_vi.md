# 1094 - Increasing Array

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Bạn muốn biến đổi mảng sao cho nó là dãy tăng dần, tức là mỗi phần tử ít nhất phải lớn hơn hoặc bằng phần tử trước đó.

Mỗi bước, bạn có thể tăng giá trị của bất kỳ phần tử nào lên một đơn vị. Hỏi số bước tối thiểu cần thực hiện là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: các phần tử của mảng.

# Kết quả

In ra số bước tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 2 5 1 7
```

Kết quả:

```cpp
5
```
