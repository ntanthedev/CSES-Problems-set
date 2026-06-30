# DEEPSEEK.MD — CSES Crawler Project Instructions

> AI agent instructions for this project. Loaded at session start to ensure consistent behavior across all future work.

---

## Project Overview

**CSES Crawler** — download, translate (EN→VI), and upload CSES Problem Set solutions to `oj.thptchuyenhatinh.edu.vn`.

- **Language**: Python
- **Site**: https://oj.thptchuyenhatinh.edu.vn
- **User**: ntannn
- **Total problems**: 400 across 18 category folders
- **Each problem**: `statement_en.md` + `analysis_en.md` + `solution.cpp` + `tests_XXXX.zip`
- **Translations**: `statement_vi.md` + `analysis_vi.md` per problem (800 files total — DONE ✅)

---

## Translation Rules (MANDATORY)

When translating CSES problems from English to Vietnamese, follow these rules strictly:

### 1. Preserve EXACTLY (zero modification)
- Math: `$...$`, `$$...$$`, `~...~` — copy character-for-character
- Code blocks: ` ```...``` ` and inline `` `...` ``
- All numbers, variables, function names, symbols, links, images (`![](hash)`)
- Markdown structure: `#` levels, bullets, tables, bold/italic

### 2. Section headings (translate in-place)
| English | Vietnamese |
|---|---|
| Input | Dữ liệu vào |
| Output | Kết quả |
| Constraints | Giới hạn |
| Example | Ví dụ |
| Explanation | Giải thích |
| References | Tài liệu tham khảo |

**Do NOT add, remove, or reorder sections.**

### 3. Terminology (MUST be consistent)
| English | Vietnamese |
|---|---|
| array | mảng |
| string | xâu |
| prefix sum | tổng tiền tố |
| segment tree | cây phân đoạn |
| binary search | tìm kiếm nhị phân |
| dynamic programming | quy hoạch động |
| graph | đồ thị |
| node / vertex | đỉnh |
| edge | cạnh |
| tree | cây |
| subtree | cây con |
| weight | trọng số |
| query | truy vấn |
| time/space complexity | độ phức tạp thời gian/bộ nhớ |
| test case | bộ test |
| time limit | giới hạn thời gian |
| memory limit | giới hạn bộ nhớ |

For terms not in this table, use common CP Vietnamese translation and stay consistent within the article.

### 4. Style
- Clear, natural Vietnamese
- Neutral address ("bạn" / no personal address)
- No commentary, no summaries, don't skip any sentence
- Output ONLY the translated Markdown — no ` ```markdown ` wrappers

### 5. Self-check (BEFORE writing)
Count of `$...$`, `$$...$$`, `~...~`, and ` ``` ` blocks in the translation **MUST EQUAL** the original. If different, fix before saving.

---

## Subagent Strategy (for bulk work)

### Agent selection
| ❌ DO NOT USE | ✅ USE |
|---|---|
| `Explore` agent | Default agent (no `agentName`) |
| Read-only, can't write files | Can use `create_file` autonomously |

### Model format
```yaml
# CORRECT:
model: "DeepSeek V4 Flash (deepseek)"
model: "DeepSeek V4 Pro (deepseek)"

# WRONG:
model: "DeepSeek V4 Flash (copilot)"   # vendor mismatch!
```

### Batch sizing
| Parameter | Value |
|---|---|
| Problems per subagent | 6–9 |
| Files per subagent | 12–18 (statement + analysis × problems) |
| Subagents per wave | 5–8 (safe), up to 22 (proven) |
| Total subagents for 400 problems | ~50–60 |

### Token efficiency
- Embed translation rules directly in each subagent prompt (~200 words) — subagents can't read memory files
- Keep prompts concise: problem list + base path + rules
- Use `DeepSeek V4 Flash (deepseek)` for subagents (50–70% cheaper than Pro)

### Quality control
- Verify first batch thoroughly before running the rest
- Spot-check 2–3 random files per batch
- Check: headings, math preservation, code preservation, terminology

### Proven workflow
```
1. list_dir on target folder(s)
2. Check for existing _vi.md files (skip if done)
3. Divide problems into batches of 6–9
4. Fire all subagents simultaneously with Flash model
5. Verify file counts with Get-ChildItem
6. Spot-check 2–3 random files
```

---

## Upload Command Reference

```powershell
# Single problem with Vietnamese + English + editorial
python upload.py --site https://oj.thptchuyenhatinh.edu.vn --user ntannn --root . --only 1068 --vi --bilingual --with-editorial --editorial-public

# Multiple problems, overwrite existing
python upload.py --user ntannn --root . --only 1068 1083 1625 --vi --bilingual --with-editorial --editorial-public --overwrite
```

---

## Folder Structure (18 categories)

```
Introductory Problems/          (24 problems) ✅
Additional Problems I/          (30 problems) ✅
Additional Problems II/         (30 problems) ✅
Sorting and Searching/          (35 problems) ✅
Dynamic Programming/            (23 problems) ✅
Graph Algorithms/               (36 problems) ✅
Tree Algorithms/                (16 problems) ✅
Mathematics/                    (37 problems) ✅
Range Queries/                  (25 problems) ✅
String Algorithms/              (21 problems) ✅
Geometry/                       (16 problems) ✅
Advanced Techniques/            (25 problems) ✅
Bitwise Operations/             (11 problems) ✅
Counting Problems/              (18 problems) ✅
Construction Problems/          ( 8 problems) ✅
Interactive Problems/           ( 6 problems) ✅
Sliding Window Problems/        (11 problems) ✅
Advanced Graph Problems/        (28 problems) ✅
────────────────────────────────────────────
TOTAL: 400 problems, 800 _vi.md files
```

---

## Common Pitfalls

1. **Explore agent is read-only** — it returns translated text but can't write files; wastes 2× tokens
2. **Vendor format** — `(deepseek)` not `(copilot)` or `(openai)`
3. **PowerShell path resolution** — always use absolute paths like `D:\ntancode\Code\cses-crawler\...` inside `Get-ChildItem`
4. **analysis_en.md may be empty** — some problems have only a title in analysis; create `analysis_vi.md` with just the translated title
5. **Image centering** — images use hash filenames `![](hash)`. To center: test `<p align="center">![](hash)</p>` on target platform
6. **"Input:" / "Output:" in examples** — these are part of the sample I/O, translate them as "Dữ liệu vào:" / "Kết quả:"
