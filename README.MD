# CSES Problem Set Collection 

[English Version](#english) | [Phiên bản Tiếng Việt](#vietnamese)

---

<a name="english"></a>
## English Description

### Introduction
This repository contains a comprehensive collection of problems, test cases, and editorial solutions from the [CSES Problem Set](https://cses.fi/), harvested. The content has been formatted into **Markdown** for easy offline reading, personal study, and educational purposes.

### Repository Structure
The data is organized by category and then by problem ID:

```
CSES_Data_Full/
├── Category Name/           # e.g., Dynamic Programming, Sorting and Searching
│   ├── Problem_ID_Name/     # e.g., 1086_Writing Numbers
│   │   ├── statement_en.md  # The problem description
│   │   ├── analysis_en.md   # The official editorial/solution
│   │   └── tests_XXXX.zip   # Test cases for the problem
```

### Purpose
This project is intended for **educational purposes only**, assisting competitive programmers in accessing CSES resources offline or in a convenient text-based format.

### Disclaimer & Attribution
- **Source**: All problem statements, test data, and editorial content are the intellectual property of [CSES](https://cses.fi/) and its authors.
- **Credit**: Please link back to the original problem on [cses.fi](https://cses.fi/) whenever discussing or redistributing these tasks.
- **License for Content**: The text of the tasks from CSES is licensed under **Creative Commons BY-SA 4.0**.

---

<a name="vietnamese"></a>
## Phiên bản Tiếng Việt

### Giới thiệu
Repository này là nơi tổng hợp các đề bài, dữ liệu kiểm thử (test cases) và lời giải (editorial) từ trang [CSES Problem Set](https://cses.fi/). Dữ liệu được thu thập và chuyển đổi sang định dạng **Markdown**, giúp thuận tiện cho việc đọc, lưu trữ và học tập ngoại tuyến.

### Cấu trúc thư mục
Dữ liệu được tổ chức theo từng chuyên mục và tên bài toán:

```
CSES_Data_Full/
├── Tên Chuyên Mục/          # Ví dụ: Dynamic Programming, Sorting and Searching
│   ├── ID_Tên_Bài/          # Ví dụ: 1086_Writing Numbers
│   │   ├── statement_en.md  # Đề bài (Tiếng Anh)
│   │   ├── analysis_en.md   # Phân tích/Lời giải chi tiết
│   │   └── tests_XXXX.zip   # File nén chứa input/output test cases
```

### Mục đích sử dụng
Dự án này chỉ phục vụ cho **mục đích giáo dục**, hỗ trợ cộng đồng lập trình thi đấu (Competitive Programming) luyện tập và tra cứu tài liệu một cách dễ dàng hơn.

### Tuyên bố bản quyền & Ghi nguồn
- **Nguồn gốc**: Tất cả nội dung đề bài, bộ test và lời giải đều thuộc quyền sở hữu của [CSES](https://cses.fi/) và các tác giả liên quan.
- **Ghi công**: Vui lòng trích dẫn nguồn gốc từ [cses.fi](https://cses.fi/) khi bạn sử dụng hoặc chia sẻ lại các nội dung này.
- **Giấy phép nội dung**: Văn bản của các đề bài trên CSES tuân theo giấy phép **Creative Commons BY-SA 4.0**.

---

### Data / Dữ liệu
The problem statements and solutions are licensed under **Creative Commons BY-SA 4.0** (as per CSES terms).
*(Nội dung đề bài và lời giải tuân theo giấy phép Creative Commons BY-SA 4.0 theo quy định của CSES).*

---

## ⚠️ Lưu ý sinh test — Problems cần Custom Checker

Có **86/400 bài (21.5%)** không thể dùng standard diff checker. Các bài này cần custom checker vì:

| Lý do | Số lượng |
|---|---|
| **Multiple valid outputs** ("print any", "any valid solution") | 71 |
| **Floating-point tolerance** (sai số ≤ 10⁻⁶) | 5 |
| **Interactive problems** (luôn cần interactor) | 6 |
| **Any order** (thứ tự in không quan trọng) | 4 |

### Danh sách chi tiết (sắp xếp theo ID)

| ID | Tên bài | Category | Lý do |
|---|---|---|---|
| 1070 | Permutations | Introductory | any valid beautiful permutation + NO SOLUTION |
| 1087 | Shortest Subsequence | Additional I | any of several solutions |
| 1092 | Two Sets | Introductory | any valid partition + YES/NO |
| 1111 | Longest Palindrome | String | any of several solutions |
| 1134 | Prüfer Code | Advanced Graph | any order of edges |
| 1164 | Room Allocation | Sorting | any valid room assignment |
| 1193 | Labyrinth | Graph | any valid path |
| 1194 | Monsters | Graph | any valid escape path |
| 1197 | Cycle Finding | Graph | any negative cycle |
| 1640 | Sum of Two Values | Sorting | any of several solutions |
| 1641 | Sum of Three Values | Sorting | any of several solutions |
| 1642 | Sum of Four Values | Sorting | any of several solutions |
| 1666 | Building Roads | Graph | any valid solution |
| 1667 | Message Route | Graph | any valid route |
| 1668 | Building Teams | Graph | any valid team (bipartite coloring) |
| 1669 | Round Trip | Graph | any valid cycle |
| 1678 | Round Trip II | Graph | any valid directed cycle |
| 1679 | Course Schedule | Graph | any valid topological order |
| 1680 | Longest Flight Route | Graph | any valid longest path |
| 1682 | Flight Routes Check | Graph | any valid unreachable pair |
| 1683 | Planets and Kingdoms | Graph | any valid SCC labeling |
| 1684 | Giant Pizza | Graph | any valid 2-SAT assignment |
| 1685 | New Flight Routes | Advanced Graph | any valid solution |
| 1689 | Knights Tour | Graph | any valid knight's tour |
| 1691 | Mail Delivery | Graph | any valid Eulerian circuit |
| 1692 | De Bruijn Sequence | Graph | any valid bit string |
| 1693 | Teleporters Path | Graph | any valid Eulerian path |
| 1695 | Police Chase | Graph | any valid min cut |
| 1696 | School Dance | Graph | any valid maximum matching |
| 1697 | Chess Tournament | Construction | any valid solution |
| 1698 | Swap Round Sorting | Additional II | any valid solution |
| 1704 | Network Renovation | Advanced Graph | any valid solution |
| 1709 | Coin Grid | Additional II | any valid solution |
| 1711 | Distinct Routes | Graph | any valid edge-disjoint paths |
| 1725 | Dice Probability | Mathematics | **floating-point** — 6 decimal places |
| 1726 | Moving Robots | Mathematics | **floating-point** — 6 decimal places |
| 1727 | Candy Lottery | Mathematics | **floating-point** — 6 decimal places |
| 1728 | Inversion Probability | Mathematics | **floating-point** — 6 decimal places |
| 1752 | Creating Offices | Advanced Graph | any valid solution |
| 1755 | Palindrome Reorder | Introductory | any valid solution + NO SOLUTION |
| 1756 | Acyclic Graph Edges | Advanced Graph | any valid edge orientation |
| 2075 | Reversal Sorting | Additional II | any valid solution |
| 2076 | Necessary Roads | Advanced Tech | any order |
| 2077 | Necessary Cities | Advanced Tech | any order |
| 2079 | Finding a Centroid | Tree | any valid centroid |
| 2106 | Repeating Substring | String | any of several possibilities |
| 2129 | Task Assignment | Advanced Tech | any of multiple solutions |
| 2130 | Distinct Routes II | Advanced Tech | any valid solution |
| 2131 | Grid Puzzle II | Additional II | any valid grid + -1 fallback |
| 2165 | Tower of Hanoi | Introductory | multiple valid minimal-move sequences |
| 2177 | Strongly Connected Edges | Advanced Graph | any valid edge orientation |
| 2179 | Even Outdegree Edges | Advanced Graph | any valid edge orientation |
| 2195 | Convex Hull | Geometry | any order of points |
| 2205 | Gray Code | Introductory | any valid solution |
| 2214 | Inverse Inversions | Construction | any valid permutation |
| 2215 | Monotone Subsequences | Construction | any valid permutation |
| 2402 | Two Stacks Sorting | Additional II | any valid solution + IMPOSSIBLE |
| 2414 | List of Sums | Additional I | any valid solution |
| 2418 | Grid Path Construction | Construction | any valid path |
| 2423 | Filling Trominos | Construction | any valid L-tromino tiling |
| 2427 | Letter Pair Move Game | Additional I | any valid solution + -1 |
| 2430 | Binary Subsequences | Additional II | any valid solution |
| 2432 | Grid Puzzle I | Additional II | any valid solution + -1 |
| 3112 | Hidden Integer | Interactive | **interactive** — hidden integer guessing |
| 3139 | Hidden Permutation | Interactive | **interactive** — permutation discovery |
| 3140 | Inversion Sorting | Interactive | **interactive** — sorting via reversals |
| 3154 | System of Linear Equations | Mathematics | any valid solution |
| 3159 | Replace with Difference | Additional II | any valid solution + -1 |
| 3213 | Water Containers Moves | Additional I | multiple valid move sequences + -1 |
| 3225 | Inverse Suffix Array | String | any of several possible strings |
| 3228 | Permuted Binary Strings | Interactive | **interactive** — permutation via binary queries |
| 3273 | Colored Chairs | Interactive | **interactive** — finding adjacent chairs |
| 3294 | Subarray Sum Constraints | Additional I | any valid solution + NO fallback |
| 3305 | K-th Highest Score | Interactive | **interactive** — finding k-th via queries |
| 3308 | Graph Coloring | Advanced Graph | any valid solution |
| 3311 | Grid Coloring I | Introductory | any valid solution + IMPOSSIBLE |
| 3312 | Grid Coloring II | Additional II | any valid solution + IMPOSSIBLE |
| 3355 | Sum of Four Squares | Mathematics | any valid decomposition |
| 3358 | Split into Two Paths | Advanced Graph | any valid solution |
| 3361 | Two Array Average | Additional I | **floating-point** — tolerance 10⁻⁶ |
| 3399 | Raab Game I | Introductory | any valid example + YES/NO |
| 3403 | Longest Common Subsequence | DP | any of several solutions |
| 3404 | Permutation Subsequence | Additional I | any of several solutions |
| 3422 | Third Permutation | Construction | any valid permutation |
| 3423 | Permutation Prime Sums | Construction | any valid permutation pairs |
| 3424 | Distinct Sums Grid | Construction | any valid grid |

### Phân loại theo lý do

| Loại custom checker | Số bài | Ghi chú |
|---|---|---|
| **"Print any" / multiple valid** | 71 | Cần checker duyệt tất cả đáp án hợp lệ |
| **Floating-point tolerance** | 5 | Cần so sánh với sai số ε = 10⁻⁶ |
| **Interactive** | 6 | Cần viết interactor riêng (giao tiếp 2 chiều) |
| **Any order** | 4 | Đầu ra không theo thứ tự cố định |

> 💡 **Mẹo triển khai**: Với các bài "print any", có thể dùng checker đọc output thí sinh rồi tự verify tính hợp lệ thay vì so với đáp án mẫu. Các bài interactive cần viết interface riêng cho từng bài. Các bài floating-point cần so sánh sai số tuyệt đối/tương đối.
