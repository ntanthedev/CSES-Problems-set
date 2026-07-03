# CSES Checker Strategy **v2** — sau đợt audit 70 checker

> Thay thế §3b–§5 của `CHECKER_STRATEGY.md` (các phần §1, §2, §2b, §6, §7, §8 —
> cơ chế judge, manifest, any-order, interactive — vẫn đúng nguyên, không đổi).
> Lý do có v2: đợt audit cho thấy **~53% checker do Composer 2.5 sinh ra có lỗi**,
> và quan trọng hơn — **các lỗi lặp lại theo đúng 6 khuôn mẫu**, nghĩa là chặn
> được bằng quy tắc trong prompt + bằng test tự động, chứ không phải "model kém".

---

## 0. Một lưu ý về chính báo cáo audit

Con số tóm tắt trong `analysis_results.md` (33 PASSED / 20 WARNING / 17 FAILED)
**không khớp với bảng chi tiết của chính nó**: đếm từng dòng trong bảng ra
**29 PASSED / 20 WARNING / 21 FAILED**. Không rõ bên nào đúng, và bản thân báo
cáo do model sinh ra cũng có thể sai theo cả hai chiều (bỏ sót bug, hoặc kết án
oan một checker đúng). Kết luận thực hành: **đừng tin danh sách PASSED của
Gemini** — chạy `validate_checker_v2.py --all` trên **toàn bộ 70 bài** (mất vài
phút) rồi lấy kết quả máy làm chuẩn, chỉ đọc tay những chỗ máy đánh WARN.

---

## 1. Vì sao 53% hỏng — chẩn đoán gốc

Prompt v1 đã đúng ở tầng "chiến lược" (đọc `ans` lấy scalar, `quitf` thay
`ensuref`, `seekEof`), nhưng **thiếu tầng "phòng thủ dữ liệu bẩn"**: nó mô tả
checker phải kiểm tra *gì*, mà không ép kiểm tra *bằng idiom nào*. Model vì thế
tự do chọn `stoi`, `readLine`, `vector(k)`… — toàn những lựa chọn trông vô hại
trong happy path và chỉ nổ khi thí sinh in ra rác. Validator v1 cũng chỉ chạy
happy path (vài case đầu = case nhỏ nhất, không giới hạn RAM/thời gian, không
có input thù địch) nên lọt hết.

V2 sửa cả hai đầu: **prompt ép idiom cụ thể** (mục 2–3) và **validator tấn công
checker như một thí sinh phá hoại** (mục 5).

## 2. Bảng quy đổi: 6 nhóm bug → idiom bắt buộc

| # | Bug thực tế đã gặp | Idiom BẮT BUỘC thay thế |
|---|---|---|
| 1 | `inf.readLine()` sau `inf.readInt()` → trôi toàn bộ grid (1193, 1194, 3311, 3312) | Đọc mỗi hàng grid bằng `readToken()` (tự bỏ qua whitespace). **Cấm `readLine` trên cả `inf` lẫn `ouf`.** |
| 2 | `stoi/stoll/atoi` trên token của thí sinh → exception không bắt → crash judge (≥17 bài) | **Mọi** số đọc từ `ouf` phải qua `ouf.readInt(lo, hi, "tên")` / `ouf.readLong(lo, hi, "tên")` — testlib tự validate định dạng, cận, tràn số và tự quit `_pe`/`_wa`. `stoll` chỉ được phép trên token của `ans` (dữ liệu jury, đáng tin). Với bài có sentinel (`-1`/`IMPOSSIBLE`): **đọc `ans` trước** để biết nhánh, rồi mới đọc `ouf` theo kiểu đã biết (xem skeleton). |
| 3 | Checker tự giải lại bài → TLE/OOM ở test max (1752 LCA K², 1697 ma trận N², 1111 `string::find`, 1092 `std::set` 10⁶) | Ngân sách cứng: **thời gian ≤ O((n+m)·log), bộ nhớ ≤ O(n+m)**. Optimum đọc từ `ans`, checker chỉ *xác minh* cấu trúc thí sinh khai (mô phỏng path, đếm bậc, multi-source BFS một lần) — không bao giờ *giải lại* (max-flow, MCMF, suffix array, LCA từng cặp, so khớp xâu O(N·M)). |
| 4 | Sai invariant: nhận I-tromino thay L (2423), ép `k == k_ans` khi đề cho `k ≤ 1000` (2427), lấy nhầm cạnh trong đa đồ thị (1197), hash 1 mod (3225) | Prompt ép model **chép nguyên văn điều kiện hợp lệ từ đề vào comment header** rồi code theo đó; phân biệt rõ "tối ưu = so với `ans`" và "trong ngưỡng = so với hằng số trong đề"; đồ thị phải xử lý **đa cạnh + khuyên** (multiset cạnh); cấm hash xác suất — so sánh phải tất định. |
| 5 | `vector<int> path(k)` trước khi kiểm tra k → `bad_alloc` với k = 2·10⁹ (1667, 1669, 1678, 1711) | Tự khỏi khi tuân thủ nhóm 2: cận trong `readInt(lo, hi, ...)` chặn k **trước** mọi cấp phát. Quy tắc phụ: không cấp phát bất kỳ thứ gì có kích thước lấy từ số thí sinh in ra khi số đó chưa qua bounded read. |
| 6 | `ouf.readEoln()` / `ouf.readEof()` → PE oan vì thừa một dấu cách/xuống dòng | Đọc thuần token; kết thúc **đúng một mẫu duy nhất**: `if (!ouf.seekEof()) quitf(_wa, "extra information in the output file");`. Cấm `readEoln`/`readEof` trên `ouf`, cấm `ouf.seekEof();` trơ (bỏ giá trị trả về = no-op). |

Cộng thêm hai quy tắc verdict từ v1 (vẫn giữ): `quitf(_wa,...)` — không bao giờ
`ensuref`/`assert` (exit 3/SIGABRT ≠ WA); thông điệp WA phải mô tả đúng lỗi của
**thí sinh** ở nhánh đó, kèm chỉ số/giá trị (1691, 1693, 2215, 2402 từng in
thông báo ngược nhánh).

## 3. File mẫu `checker_skeleton.cpp`

Đi kèm gói này là `checker_skeleton.cpp` — một checker **compile được nguyên
trạng**, mỗi idiom phòng thủ đều có comment trỏ về nhóm bug nó tiêu diệt, kèm
"header contract" (Problem / Input read / Validity / Optimality / Complexity)
mà mọi checker sinh ra phải điền. Model chép template tốt hơn nhiều so với làm
theo mô tả — **luôn đưa file này vào input của Composer** cùng đề bài và
solution.

## 4. PROMPT v2 gửi Composer 2.5 (thay toàn bộ prompt §4 cũ)

Feed cho mỗi bài: `statement_en.md` + `solution.cpp` + `checker_skeleton.cpp`.
Ghi kết quả vào `<problem_dir>/checker.cpp`.

```
You are a competitive-programming problem-setter writing a testlib.h checker
for a CSES problem that accepts multiple valid answers, to run on a DMOJ/VNOJ
judge ("bridged" + "testlib": invoked as `checker input output judge_answer`;
exit 0 = AC, 1 = WA, 2 = PE; exit 3 means "assertion failed", NOT WA).

INPUT PROVIDED:
- statement_en.md   the full problem statement, constraints included
- solution.cpp      a reference solution; its output is A valid answer and may
                    legitimately differ byte-for-byte from the judge file
- checker_skeleton.cpp  the mandatory style template — copy its structure,
                    helper patterns, and header-contract comment block
- testlib.h is available at the standard include path; do not reproduce it

WRITE checker.cpp. HARD RULES — every one of these was violated by a previous
batch and caused a production incident; violations mean the checker is rejected:

A. READING
A1. inf is trusted: plain inf.readInt()/readToken(), no bounds, no readEoln.
A2. NEVER call readLine() on inf or ouf. Grids and per-line data are read one
    readToken() per row/cell (readInt does not consume the trailing newline,
    so a following readLine returns "" and shifts every row).
A3. EVERY number read from ouf MUST use explicit bounds and a variable name:
        int k = ouf.readInt(2, n + 1, "k");
        long long c = ouf.readLong(0LL, MAXC, "total cost");
    Never a bare ouf.readInt(). Never stoi/stol/stoll/atoi/atol/strtol on any
    token that came from ouf (they throw or overflow on garbage; testlib's
    bounded readers reject it safely as PE/WA instead). stoll on ans tokens is
    allowed — ans is trusted jury data.
A4. Never allocate memory whose size comes from a contestant number unless
    that number already passed a bounded read (rule A3 makes this automatic).
A5. Sentinel answers ("-1", "IMPOSSIBLE", "NO"): decide the branch from ans
    FIRST (read ans's first token), then read ouf expecting exactly that
    shape. If ans is the sentinel and ouf is not (or vice versa), quitf(_wa)
    with a message that names what the CONTESTANT did wrong in THAT branch.

B. WHAT TO CHECK
B1. Verify EVERY validity constraint the statement puts on the output: values
    in range, permutation/distinctness, edges exist in the input (multigraphs:
    count parallel edges with a multiset — never "find first edge u-v"; respect
    self-loops), path steps are adjacent and on the grid, shapes match exactly
    (an L-tromino's 3 cells have a 2x2 bounding box — 3 collinear cells must
    be rejected), counts printed equal counts delivered.
B2. Optimality scalars (min/max k, cost, length): read them from ans with
    ans.readInt()/readLong()/readToken() and require ouf to match. NEVER
    re-solve the problem in the checker (no max-flow, MCMF, suffix arrays,
    LCA over all pairs, brute force). Verifying the contestant's claimed
    structure is fine; recomputing the optimum is not.
B3. If the statement allows ANY answer within a stated bound ("at most 1000
    moves"), compare against that stated bound, NOT against ans's move count.
B4. All comparisons must be deterministic — no probabilistic hashing. If you
    need to compare strings/suffixes at scale, use an exact linear method.
B5. Complexity budget for the checker itself: O((n+m) log(n+m)) time and
    O(n+m) memory at the statement's maximum constraints. Forbidden: O(n^2)
    adjacency matrices for n > 3000, pairwise loops over contestant-chosen
    vertex sets (use one multi-source BFS instead), std::string::find over
    10^5+ haystacks (use KMP/Z), std::set where a sorted vector works at 10^6.

C. VERDICTS & TERMINATION
C1. Failure => quitf(_wa, "...") always. NEVER ensuref/ensure/assert on
    anything derived from ouf (exit 3 / SIGABRT is shown as a judge error,
    not WA). _pe only for genuine token-format problems testlib didn't
    already catch.
C2. WA messages describe the contestant's actual mistake with concrete
    indices/values ("edge 3 connects 5 and 7, but 7 was already matched"),
    and must match their branch — never print the jury-side description of
    the opposite mistake.
C3. End with EXACTLY:
        if (!ouf.seekEof()) quitf(_wa, "extra information in the output file");
    Not bare ouf.seekEof(); (return value ignored = no-op). Not ouf.readEof()
    (doesn't skip trailing whitespace). Never ouf.readEoln() anywhere.

D. DOCUMENTATION
D1. Start the file with the skeleton's header-contract comment, filled in:
    Problem / Input read / Validity rules enforced (quote them from the
    statement) / Optimality source / Complexity. A human reviews this block
    against the statement before the checker is trusted.

SELF-CHECK before you finish (fix and re-check on any "no"):
- Zero occurrences of: readLine, readEoln, ouf.readEof, ensuref, ensure(,
  assert(, and of stoi/stoll/atoi applied to ouf data?
- Every ouf.readInt/readLong call has (lo, hi, "name")?
- Sentinel branch (if the problem has one) decided from ans first?
- Optimum compared to ans's scalar (or the statement's bound, rule B3) —
  and no heavy algorithm anywhere in the file?
- Would solution.cpp's own output pass even where its bytes differ from the
  judge file?
- Header contract filled in and consistent with the code?

Output ONLY the C++ source. No explanation, no ```cpp wrapper.
```

## 5. Validator v2 — chạy thế nào, bắt được gì

`validate_checker_v2.py` (đi kèm) thay hẳn bản v1. Khác biệt chính:

1. **Static lint** trước khi chạy: quét `checker.cpp` (đã bóc comment/string để
   khỏi false-positive) tìm đúng các pattern cấm ở mục 2, in kèm số dòng.
2. **Chọn case thông minh**: vài case đầu (nhỏ, test logic) **cộng các case lớn
   nhất theo dung lượng input** — v1 chỉ lấy case đầu nên không bao giờ thấy
   TLE/OOM nhóm 3.
3. **Chạy checker trong lồng tài nguyên**: RAM giới hạn `--mem` (mặc định 512 MB,
   khớp judge) qua `RLIMIT_AS`, thời gian `--checker-tl` (mặc định `max(5, 4×TL
   của bài)` — TL đọc tự động từ `statement_en.md`). Hết RAM/treo = FAIL.
4. **Bộ input thù địch (hostile)** — thứ thí sinh thật sẽ in ra: output rỗng,
   token chữ, số 20 chữ số (tràn `long long`), số đầu tiên thay bằng 2·10⁹
   (bẫy cấp phát) và −1. Checker **crash/treo trên bất kỳ cái nào = FAIL cứng**
   (trên OJ đó là Internal Error cho cả lượt chấm); AC output rỗng/rác/tràn số
   cũng là FAIL (lỏng nguy hiểm).
5. **Bộ whitespace** — đáp án đúng + xuống dòng thừa / CRLF / thiếu newline
   cuối: phải AC, không thì WARN "sẽ phạt oan học sinh" (nhóm 6).
6. **Mutation mở rộng** (5 phép, thêm đổi-1-ký-tự và nhân-đôi-dòng cho bài
   grid/xâu) — vẫn là WARNING heuristic như v1, đọc tay khi không phép nào bị
   từ chối.
7. **Batch + báo cáo**: chạy cả repo một lệnh, bảng tổng kết PASS/WARN/FAIL +
   thời gian chạy tối đa của checker, `--json report.json` để diff giữa các đợt.

```bash
# toàn bộ 70 bài có checker.cpp trong repo:
python validate_checker_v2.py --all /path/to/CSES-Problems-set --json audit_v2.json

# chỉ nhóm cần sinh lại:
python validate_checker_v2.py --all . --only 1193 1194 3311 3312 --json fix1.json
```

Validator ĐÃ được kiểm chứng hai chiều trong sandbox trước khi bàn giao: một
checker viết đúng chuẩn → PASS/exit 0; một checker cấy đúng các bug nhóm
2/5/6 → lint chỉ đúng dòng, hostile suite bắt `std::invalid_argument`/
`std::bad_alloc`/`std::out_of_range` (đều SIGABRT), whitespace suite báo PE
oan → FAIL/exit 1.

**Giới hạn cần biết (validator không thay được người):** nó không chứng minh
được invariant *ngữ nghĩa* — kiểu 2423 nhận I-tromino, hay 2427 ép `k == k_ans`
khi đề cho `k ≤ 1000` — nếu mutation ngẫu nhiên không tình cờ chạm vào. Đó là
việc của bước review header-contract (quy tắc D1): người đọc so khối comment
đầu file với đề bài, mất ~1 phút/bài, chỉ cần làm cho các bài WARN.

## 6. Quy trình khắc phục 70 bài hiện tại (đề xuất thứ tự)

1. Chạy `validate_checker_v2.py --all` trên **cả 70 bài** → lấy danh sách
   FAIL/WARN theo máy (đừng dùng danh sách của Gemini làm nguồn duy nhất — xem
   mục 0).
2. Với mọi bài FAIL/WARN: cho Composer 2.5 **sinh lại từ đầu bằng prompt v2 +
   skeleton** (đừng bảo nó "vá" checker cũ — vá giữ nguyên cấu trúc hỏng).
   Danh sách theo báo cáo hiện tại để tham khảo/ước lượng khối lượng (41 bài):
   - FAILED (21): `1111 1193 1194 1197 1640 1641 1642 1667 1669 1678 1691 1693 1697 1752 2106 2423 2427 3154 3225 3311 3312`
   - WARNING (20): `1070 1092 1164 1668 1679 1682 1684 1711 2075 2177 2179 2215 2402 2414 3159 3213 3355 3422 3423 3424`
3. Validate lại đúng nhóm vừa sinh (`--only ...`), lặp đến khi hết FAIL; đọc
   tay header-contract của các bài còn WARN.
4. Upload lại: `python upload.py --user ntannn --root . --only <ids> --vi --with-editorial --editorial-public --overwrite`.
5. **Kiểm chứng end-to-end trên OJ thật** cho ~3 bài đại diện (1 grid, 1 bài có
   sentinel, 1 bài đồ thị lớn): submit `solution.cpp` → AC; submit một bài cố
   tình in `abc` → phải ra WA/PE chứ **không** phải Internal Error. Đây là lớp
   kiểm tra duy nhất chạy đúng binary judge của CHT-oj (validator local mô
   phỏng contract nhưng không phải môi trường thật).

## 7. Các lưu ý vận hành còn lại (chuyển tiếp từ v1, vẫn còn hiệu lực)

- 4 bài "any order" (2076, 2077, 1134, 2195) dùng 3 checker generic viết tay —
  **không sinh lại bằng model**, đã pass kiểm chứng riêng.
- 5 bài floats: đọc epsilon từ đề bằng tay, vào manifest với
  `floats/floatsabs/floatsrel` — không cần checker.cpp.
- 6 bài interactive: vẫn làm tay qua browser (hoặc gửi output
  `--inspect-fields` để wire `grader`/`custom_grader` vào upload.py).
- 3 zip hỏng (2133, 3410, 3411): nhớ tải lại trước khi bài đó vào manifest.
- Đừng quên: một entry manifest sai `checker_file` sẽ nổ đúng traceback
  `TypeError: check() missing ... 'files'` lúc chấm — đã ghi trong §7 tài liệu cũ.
