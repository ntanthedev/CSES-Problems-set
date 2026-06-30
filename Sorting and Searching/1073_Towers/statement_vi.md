# 1073 - Towers

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ khối lập phương theo một thứ tự nhất định, nhiệm vụ của bạn là xây các tòa tháp từ chúng. Khi hai khối lập phương được đặt chồng lên nhau, khối ở trên phải nhỏ hơn khối ở dưới.

Bạn phải xử lý các khối lập phương theo thứ tự đã cho. Với mỗi khối, bạn có thể đặt nó lên trên một tòa tháp hiện có, hoặc bắt đầu một tòa tháp mới. Hỏi số lượng tòa tháp tối thiểu có thể là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng khối lập phương.

Dòng tiếp theo chứa $n$ số nguyên $k\_1,k\_2,\ldots,k\_n$: kích thước của các khối lập phương.

# Kết quả

In ra một số nguyên: số lượng tòa tháp tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le k\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 8 2 1 5
```

Kết quả:

```cpp
2
```
