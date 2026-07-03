#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
validate_checker_v2.py — kiểm định checker testlib TRƯỚC khi đưa lên OJ.

Nâng cấp từ v1 sau báo cáo phân tích 70 checker (53% có lỗi). v1 chỉ bắt được
"checker quá chặt" (từ chối đáp án hợp lệ) và một phần "quá lỏng" (mutation).
v2 bắt đủ 6 nhóm bug đã gặp trong thực tế:

  Nhóm 1  Trôi dòng grid (readLine sau readInt)  -> static lint + self-check
  Nhóm 2  stoi/stoll không an toàn trên ouf      -> lint + HOSTILE: token rác,
                                                     token 20 chữ số (overflow)
  Nhóm 3  Checker TLE/OOM ở test cực hạn          -> chạy trên các test LỚN NHẤT
                                                     với giới hạn RAM + đo thời gian
  Nhóm 4  Sai invariant / quá lỏng                -> mutation mở rộng (5 phép)
  Nhóm 5  Cấp phát vector(k) trước khi check k    -> HOSTILE: k = 2*10^9 chạy
                                                     dưới RLIMIT_AS -> crash bị bắt
  Nhóm 6  Khắt khe khoảng trắng (readEoln/readEof)-> WHITESPACE: thêm \\n, space,
                                                     CRLF vào đáp án đúng -> phải AC

Nguyên tắc phân loại:
  * Checker CRASH (signal / exit code lạ / treo / hết RAM) trên dữ liệu mà thí
    sinh kiểm soát được  -> FAIL cứng. Trên OJ đây là "Internal Error" cho cả
    lượt chấm, tệ hơn mọi WA.
  * Checker AC output rỗng / token rác / số tràn long long -> FAIL cứng (quá lỏng
    đến mức nguy hiểm).
  * Mutation không bị từ chối, whitespace bị từ chối, lint bẩn -> WARNING (đọc tay).

USAGE
    python validate_checker_v2.py PROBLEM_DIR [PROBLEM_DIR ...]
    python validate_checker_v2.py --all /path/to/CSES-Problems-set [--only 1193 1194]
    # tuỳ chọn: --cases 6 --mem 512 --checker-tl 10 --json report.json --testlib PATH
    #           --skip-solution  (không chạy solution.cpp — dùng khi reference chưa AC)

PROBLEM_DIR cần có: checker.cpp, tests_<ID>.zip (N.in/N.out ở gốc zip).
solution.cpp chỉ bắt buộc khi KHÔNG có --skip-solution.
statement_en.md (nếu có) được đọc để lấy time limit của bài -> suy ra ngân sách
thời gian cho checker.

EXIT CODE:  0 = mọi bài PASS (warning không tính)   1 = có ít nhất một FAIL
"""
import argparse
import glob
import json
import os
import re
import resource
import shutil
import subprocess
import sys
import tempfile
import time
import urllib.request
import zipfile

TESTLIB_URL = 'https://raw.githubusercontent.com/MikeMirzayanov/testlib/master/testlib.h'
TIME_RE = re.compile(r'Time limit:\*\*\s*([0-9.]+)\s*s', re.I)

# --------------------------------------------------------------------------- #
# tiny utils
# --------------------------------------------------------------------------- #

def die(msg):
    print('ERROR: %s' % msg, file=sys.stderr)
    sys.exit(1)


def ensure_testlib(path):
    if os.path.exists(path):
        return path
    print('Fetching testlib.h -> %s ...' % path)
    try:
        urllib.request.urlretrieve(TESTLIB_URL, path)
    except Exception as e:
        die('could not download testlib.h (%s). Pass --testlib /path/to/testlib.h.' % e)
    return path


def compile_cpp(src, out, include_dir=None, std='c++17'):
    cmd = ['g++', '-O2', '-std=%s' % std, '-o', out, src]
    if include_dir:
        cmd[1:1] = ['-I', include_dir]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        return r.stderr[-4000:]
    return None


def read_cases(zip_path):
    pairs = {}
    with zipfile.ZipFile(zip_path) as zf:
        for name in zf.namelist():
            m = re.search(r'(?:^|/)(\d+)\.(in|out)$', name, re.I)
            if m:
                pairs.setdefault(int(m.group(1)), {})[m.group(2).lower()] = name
        cases = []
        for num in sorted(pairs):
            c = pairs[num]
            if 'in' in c and 'out' in c:
                cases.append((num, zf.read(c['in']), zf.read(c['out'])))
    return cases


def classify(returncode):
    """DMOJ 'testlib' bridge: 0=AC 1=WA 2=PE 3=assert 7=partial.
    Signal deaths come back négatif (-11 = SIGSEGV, -6 = SIGABRT/bad_alloc...)."""
    if returncode == 0:
        return 'AC'
    if returncode == 1:
        return 'WA'
    if returncode == 2:
        return 'PE'
    if returncode == 3:
        return 'ASSERT'
    if returncode == 7:
        return 'PARTIAL'
    if returncode is not None and returncode < 0:
        return 'CRASH(sig%d)' % -returncode
    return 'CRASH(exit%s)' % returncode


OK_VERDICTS = ('AC', 'PARTIAL')
GRADEABLE = ('AC', 'WA', 'PE', 'PARTIAL')   # anything else on contestant data = judge crash


def _mklimits(mem_mb):
    def fn():
        b = mem_mb * 1024 * 1024
        try:
            resource.setrlimit(resource.RLIMIT_AS, (b, b))
        except Exception:
            pass
        try:
            resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
        except Exception:
            pass
    return fn


class RunResult(object):
    __slots__ = ('verdict', 'wall', 'stderr', 'timed_out')

    def __init__(self, verdict, wall, stderr, timed_out=False):
        self.verdict, self.wall, self.stderr, self.timed_out = verdict, wall, stderr, timed_out


def run_checker(binpath, in_f, out_f, ans_f, timeout, mem_mb):
    t0 = time.monotonic()
    try:
        r = subprocess.run([binpath, in_f, out_f, ans_f], capture_output=True,
                           timeout=timeout, preexec_fn=_mklimits(mem_mb))
        return RunResult(classify(r.returncode), time.monotonic() - t0,
                         r.stderr.decode(errors='replace')[:400])
    except subprocess.TimeoutExpired:
        return RunResult('TIMEOUT', time.monotonic() - t0, '', timed_out=True)


# --------------------------------------------------------------------------- #
# Phase 0 — static lint of checker.cpp (mỗi rule trỏ về một nhóm bug thực tế)
# --------------------------------------------------------------------------- #

def _strip_comments_strings(src):
    """Xoá comment + string literal (thay bằng khoảng trắng, giữ nguyên số dòng)
    để lint không dính false positive từ chuỗi thông báo."""
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if src.startswith('//', i):
            j = src.find('\n', i)
            j = n if j < 0 else j
            out.append(' ' * (j - i))
            i = j
        elif src.startswith('/*', i):
            j = src.find('*/', i)
            j = n if j < 0 else j + 2
            out.append(''.join('\n' if ch == '\n' else ' ' for ch in src[i:j]))
            i = j
        elif c in '"\'':
            q, j = c, i + 1
            while j < n and src[j] != q:
                j += 2 if src[j] == '\\' else 1
            j = min(j + 1, n)
            out.append(q + ' ' * (j - i - 2) + (q if j - i >= 2 else ''))
            i = j
        else:
            out.append(c)
            i += 1
    return ''.join(out)


LINT_RULES = [
    # (regex, mức, thông điệp)
    (r'\bensuref?\s*\(',
     'warn', 'ensure/ensuref thoát với exit code 3 (assert), không phải WA — thay bằng if(!cond) quitf(_wa,...)  [nhóm 2/verdict]'),
    (r'\bassert\s*\(',
     'warn', 'assert() abort bằng SIGABRT -> Internal Error trên judge — thay bằng quitf(_wa,...)'),
    (r'ouf\s*\.\s*readEoln',
     'warn', 'ouf.readEoln() phạt oan khoảng trắng/dòng trống của thí sinh — đọc theo token, kết thúc bằng seekEof  [nhóm 6]'),
    (r'ouf\s*\.\s*readEof\s*\(',
     'warn', 'ouf.readEof() KHÔNG bỏ qua whitespace cuối file — dùng if(!ouf.seekEof()) quitf(_wa,...)  [nhóm 6]'),
    (r'^\s*ouf\s*\.\s*seekEof\s*\(\s*\)\s*;',
     'warn', 'ouf.seekEof(); đứng một mình là no-op (bỏ qua giá trị trả về) — phải bọc trong if(!...) quitf(_wa,...)'),
    (r'\b(stoi|stol|stoll|stoul|stoull|atoi|atol|atoll|strtoll?|strtoull?)\s*\(',
     'warn', 'ép kiểu chuỗi->số thô: ném exception/UB với token rác hoặc số quá dài. OK nếu CHỈ áp dụng lên token của ans (jury); cấm tuyệt đối trên ouf — dùng ouf.readInt/readLong có cận  [nhóm 2]'),
    (r'\b(scanf|gets)\s*\(|cin\s*>>',
     'warn', 'đọc bằng scanf/cin bỏ qua toàn bộ validation của testlib — dùng inf/ouf/ans  [nhóm 2]'),
    (r'ouf\s*\.\s*readLine',
     'warn', 'ouf.readLine() dễ trôi dòng và nhạy CRLF — đọc grid/row bằng ouf.readToken()  [nhóm 1]'),
    (r'ouf\s*\.\s*read(Int|Long|LongLong)\s*\(\s*\)',
     'warn', 'ouf.readInt()/readLong() KHÔNG có cận: không chặn được k=2e9 trước khi cấp phát, không chặn tràn số — luôn truyền (lo, hi, "tên")  [nhóm 5]'),
    (r'vector\s*<\s*vector\s*<\s*(bool|char|int)',
     'info', 'ma trận 2 chiều — kiểm tra lại N tối đa: N=1e5 là ~1.25GB với vector<vector<bool>>  [nhóm 3]'),
]
_READLINE_AFTER_READINT = ('inf\\s*\\.\\s*readLine', 'inf\\s*\\.\\s*readInt')


def lint_checker(src_path):
    raw = open(src_path, encoding='utf-8', errors='replace').read()
    src = _strip_comments_strings(raw)
    lines = src.splitlines()
    findings = []
    for rx, sev, msg in LINT_RULES:
        pat = re.compile(rx, re.M)
        for i, line in enumerate(lines, 1):
            if pat.search(line):
                findings.append((sev, i, msg))
                break                    # 1 lần / rule là đủ, khỏi spam
    if re.search(_READLINE_AFTER_READINT[0], src) and re.search(_READLINE_AFTER_READINT[1], src):
        findings.append(('warn', 0,
                         'có cả inf.readInt và inf.readLine: readInt không nuốt \\n cuối dòng nên '
                         'readLine đầu tiên trả về chuỗi rỗng -> trôi toàn bộ grid. Đọc row bằng inf.readToken()  [nhóm 1]'))
    return findings


# --------------------------------------------------------------------------- #
# Mutations (SHOULD-reject) & hostile payloads (MUST-not-crash)
# --------------------------------------------------------------------------- #

def mutate(judge_out):
    """Các phép phá đáp án đúng. Checker tốt nên từ chối ÍT NHẤT một phép/case."""
    text = judge_out.decode('utf-8', errors='replace')
    lines = text.splitlines()
    nonempty = [i for i, l in enumerate(lines) if l.strip()]
    out = []

    ints = list(re.finditer(r'-?\d+', text))
    if ints:
        last = ints[-1]
        out.append(('last integer +1',
                    (text[:last.start()] + str(int(last.group()) + 1) + text[last.end():]).encode()))
    if nonempty:
        i = nonempty[-1]
        out.append(('drop last line', ('\n'.join(lines[:i]) + '\n').encode()))
        toks = lines[i].split()
        if len(toks) >= 2:
            out.append(('reverse last line tokens',
                        ('\n'.join(lines[:i] + [' '.join(reversed(toks))] + lines[i + 1:]) + '\n').encode()))
        out.append(('duplicate last line',
                    ('\n'.join(lines[:i + 1] + [lines[i]] + lines[i + 1:]) + '\n').encode()))
        # đổi 1 ký tự giữa dòng cuối (bắt checker grid/xâu quá lỏng)
        l = lines[i]
        mid = len(l) // 2
        if l[mid] not in ' \t':
            repl = 'X' if l[mid] != 'X' else 'Y'
            out.append(('flip one char in last line',
                        ('\n'.join(lines[:i] + [l[:mid] + repl + l[mid + 1:]] + lines[i + 1:]) + '\n').encode()))
    return out


def _replace_first_int(judge_out, new_tok):
    text = judge_out.decode('utf-8', errors='replace')
    m = re.search(r'-?\d+', text)
    if not m:
        return None
    return (text[:m.start()] + new_tok + text[m.end():]).encode()


def hostile_payloads(judge_out):
    """(label, bytes, ac_severity): checker TUYỆT ĐỐI không được crash/treo trên
    các output này; ac_severity nói AC ở đây nghiêm trọng cỡ nào."""
    out = [
        ('empty output', b'', 'fail'),
        ('garbage tokens', b'abc xyz !!\n', 'fail'),
        ('one huge negative', b'-999999999\n', 'warn'),
    ]
    for label, tok, sev in (('first int -> 1999999999', '1999999999', 'warn'),
                            ('first int -> 20-digit overflow', '99999999999999999999', 'fail'),
                            ('first int -> -1', '-1', 'warn')):
        b = _replace_first_int(judge_out, tok)
        if b is not None:
            out.append((label, b, sev))
    return out


def whitespace_variants(judge_out):
    """Đáp án ĐÚNG chỉ khác khoảng trắng — checker phải AC hết  [nhóm 6]."""
    return [
        ('trailing newlines + spaces', judge_out.rstrip(b'\n') + b'  \n\n \n'),
        ('CRLF line endings', judge_out.replace(b'\r\n', b'\n').replace(b'\n', b'\r\n')),
        ('no final newline', judge_out.rstrip(b'\r\n')),
    ]


# --------------------------------------------------------------------------- #
# Validate one problem dir
# --------------------------------------------------------------------------- #

def pick_cases(cases, budget):
    """Lấy vài case ĐẦU (nhỏ, kiểm tra logic) + vài case LỚN NHẤT theo kích thước
    input (bắt TLE/OOM của checker — v1 chỉ lấy case đầu nên trượt sạch nhóm 3)."""
    if len(cases) <= budget:
        return cases, set(c[0] for c in cases)
    n_small = max(1, budget - max(1, budget // 3))
    small = cases[:n_small]
    by_size = sorted(cases, key=lambda c: len(c[1]), reverse=True)
    big, chosen = [], set(c[0] for c in small)
    for c in by_size:
        if len(small) + len(big) >= budget:
            break
        if c[0] not in chosen:
            big.append(c)
            chosen.add(c[0])
    big_ids = set(c[0] for c in big)
    picked = sorted(small + big, key=lambda c: c[0])
    return picked, big_ids


def problem_time_limit(pdir):
    st = os.path.join(pdir, 'statement_en.md')
    if os.path.exists(st):
        m = TIME_RE.search(open(st, encoding='utf-8', errors='replace').read())
        if m:
            return float(m.group(1))
    return None


def validate_problem(pdir, opt, testlib_dir):
    name = os.path.basename(os.path.abspath(pdir))
    rep = {'problem': name, 'status': 'PASS', 'failures': [], 'warnings': [],
           'lint': [], 'max_checker_wall': 0.0}

    def fail(msg):
        rep['failures'].append(msg)
        print('    FAIL: %s' % msg)

    def warn(msg):
        rep['warnings'].append(msg)
        print('    warn: %s' % msg)

    checker_src = os.path.join(pdir, 'checker.cpp')
    solution_src = os.path.join(pdir, 'solution.cpp')
    zips = sorted(glob.glob(os.path.join(pdir, 'tests_*.zip')))
    if not os.path.exists(checker_src):
        fail('missing checker.cpp')
    if not opt.skip_solution and not os.path.exists(solution_src):
        fail('missing solution.cpp (pass --skip-solution to omit)')
    if not zips:
        fail('missing tests_*.zip')
    if rep['failures']:
        rep['status'] = 'FAIL'
        return rep

    # ---- phase 0: lint ----
    for sev, ln, msg in lint_checker(checker_src):
        rep['lint'].append({'severity': sev, 'line': ln, 'msg': msg})
        tag = 'lint!' if sev == 'warn' else 'lint '
        print('    %s %s %s' % (tag, ('L%-4d' % ln) if ln else '     ', msg))
        if sev == 'warn':
            rep['warnings'].append('lint L%d: %s' % (ln, msg))

    # ---- compile ----
    workdir = tempfile.mkdtemp(prefix='ckv2_')
    try:
        checker_bin = os.path.join(workdir, 'checker')
        solution_bin = os.path.join(workdir, 'solution')
        err = compile_cpp(checker_src, checker_bin, include_dir=testlib_dir)
        if err:
            fail('checker.cpp does not compile:\n%s' % err)
            rep['status'] = 'FAIL'
            return rep
        if not opt.skip_solution:
            err = compile_cpp(solution_src, solution_bin)
            if err:
                fail('solution.cpp does not compile:\n%s' % err)
                rep['status'] = 'FAIL'
                return rep

        try:
            cases = read_cases(zips[0])
        except zipfile.BadZipFile:
            fail('corrupt zip: %s' % os.path.basename(zips[0]))
            rep['status'] = 'FAIL'
            return rep
        if not cases:
            fail('zip has no N.in/N.out pairs')
            rep['status'] = 'FAIL'
            return rep

        tl = problem_time_limit(pdir)
        checker_tl = opt.checker_tl or max(5.0, 4.0 * (tl or 1.0))
        picked, big_ids = pick_cases(cases, opt.cases)
        hostile_done = 0
        print('    cases: %s (of %d; * = largest-by-size, checker budget %.0fs / %dMB)'
              % (', '.join(('%d*' % n) if n in big_ids else str(n) for n, _, _ in picked),
                 len(cases), checker_tl, opt.mem))

        for num, inp, judge_out in picked:
            in_f = os.path.join(workdir, 'c.in')
            judge_f = os.path.join(workdir, 'c.judge')
            out_f = os.path.join(workdir, 'c.out')
            open(in_f, 'wb').write(inp)
            open(judge_f, 'wb').write(judge_out)

            def check(bytes_out, label):
                open(out_f, 'wb').write(bytes_out)
                r = run_checker(checker_bin, in_f, out_f, judge_f, checker_tl, opt.mem)
                rep['max_checker_wall'] = max(rep['max_checker_wall'], r.wall)
                return r

            # A. MUST-AC: judge vs itself (cũng là perf test trên case lớn)
            r = check(judge_out, 'self')
            if r.timed_out:
                fail('case %d: checker TIMED OUT (%.1fs) on judge output — checker quá chậm [nhóm 3]' % (num, r.wall))
            elif r.verdict not in OK_VERDICTS:
                fail('case %d: judge-output self-check -> %s  %s' % (num, r.verdict, r.stderr[:200]))
            elif r.wall > checker_tl * 0.5:
                warn('case %d: checker took %.1fs on judge output (budget %.0fs) — sát giới hạn [nhóm 3]'
                     % (num, r.wall, checker_tl))

            # B. solution.cpp output (optional — chỉ khi reference đáng tin)
            if not opt.skip_solution:
                try:
                    sol = subprocess.run([solution_bin], input=inp, capture_output=True, timeout=60)
                    r = check(sol.stdout, 'sol')
                    if r.timed_out:
                        warn('case %d: checker TIMED OUT on solution output [nhóm 3]' % num)
                    elif r.verdict not in OK_VERDICTS:
                        warn('case %d: solution.cpp output -> %s (reference có thể chưa AC)  %s'
                             % (num, r.verdict, r.stderr[:200]))
                except subprocess.TimeoutExpired:
                    warn('case %d: solution.cpp timed out — skipped solution-output test' % num)

            # C. whitespace-tolerance: các biến thể CHỈ khác khoảng trắng phải AC
            for label, wout in whitespace_variants(judge_out):
                r = check(wout, label)
                if r.timed_out or r.verdict not in GRADEABLE:
                    fail('case %d: checker crashed on "%s" -> %s [nhóm 6]' % (num, label, r.verdict))
                elif r.verdict not in OK_VERDICTS:
                    warn('case %d: "%s" -> %s — checker khắt khe khoảng trắng, học sinh sẽ bị PE oan [nhóm 6]'
                         % (num, label, r.verdict))

            # D. mutations: nên từ chối ít nhất một phép
            rejected_any = False
            for label, bad in mutate(judge_out):
                r = check(bad, label)
                if r.timed_out or r.verdict not in GRADEABLE:
                    fail('case %d: checker crashed on mutation "%s" -> %s [nhóm 2/5]' % (num, label, r.verdict))
                elif r.verdict not in OK_VERDICTS:
                    rejected_any = True
            if not rejected_any:
                warn('case %d: KHÔNG mutation nào bị từ chối — checker có thể quá lỏng, đọc tay [nhóm 4]' % num)

            # E. hostile: chỉ chạy trên 2 case (1 nhỏ nhất + 1 lớn nhất) cho đỡ tốn
            if hostile_done < 2 and (hostile_done == 0 or num in big_ids):
                hostile_done += 1
                for label, bad, ac_sev in hostile_payloads(judge_out):
                    r = check(bad, label)
                    if r.timed_out:
                        fail('case %d: checker HUNG on hostile "%s" [nhóm 3/5]' % (num, label))
                    elif r.verdict not in GRADEABLE:
                        fail('case %d: checker CRASHED on hostile "%s" -> %s  %s [nhóm 2/5]'
                             % (num, label, r.verdict, r.stderr[:160]))
                    elif r.verdict == 'ASSERT':
                        warn('case %d: hostile "%s" -> exit 3 (assert) thay vì WA/PE — thí sinh thấy verdict khó hiểu' % (num, label))
                    elif r.verdict in OK_VERDICTS:
                        if ac_sev == 'fail':
                            fail('case %d: hostile "%s" được AC — checker lỏng nghiêm trọng [nhóm 4]' % (num, label))
                        else:
                            warn('case %d: hostile "%s" được AC — kiểm tra lại bằng tay' % (num, label))
    finally:
        shutil.rmtree(workdir, ignore_errors=True)

    rep['status'] = 'FAIL' if rep['failures'] else ('WARN' if rep['warnings'] else 'PASS')
    return rep


# --------------------------------------------------------------------------- #

def find_all_problems(root, only):
    dirs = []
    for cat in sorted(os.listdir(root)):
        cdir = os.path.join(root, cat)
        if not os.path.isdir(cdir) or cat.startswith('.'):
            continue
        for folder in sorted(os.listdir(cdir)):
            pdir = os.path.join(cdir, folder)
            m = re.match(r'^\s*(\d+)[_\-\s]', folder)
            if not os.path.isdir(pdir) or not m:
                continue
            if only and m.group(1) not in only:
                continue
            if os.path.exists(os.path.join(pdir, 'checker.cpp')):
                dirs.append(pdir)
    return dirs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('problem_dirs', nargs='*', help='Một hoặc nhiều thư mục bài.')
    ap.add_argument('--all', metavar='ROOT', help='Quét toàn bộ repo CSES-Problems-set, chạy mọi bài có checker.cpp.')
    ap.add_argument('--only', nargs='*', help='(với --all) chỉ các CSES id này.')
    ap.add_argument('--cases', type=int, default=6, help='Số case mỗi bài: vài case đầu + vài case lớn nhất (mặc định 6).')
    ap.add_argument('--mem', type=int, default=512, help='RAM tối đa cho checker, MB (mặc định 512 — khớp judge).')
    ap.add_argument('--checker-tl', type=float, default=None,
                    help='Ngân sách thời gian cho checker mỗi lần chạy, giây. Mặc định: max(5, 4×TL của bài).')
    ap.add_argument('--testlib', default=os.path.join(tempfile.gettempdir(), 'testlib.h'))
    ap.add_argument('--json', metavar='PATH', help='Ghi báo cáo JSON tổng hợp ra file.')
    ap.add_argument('--skip-solution', action='store_true',
                    help='Bỏ qua solution.cpp: không biên dịch/chạy; solution mismatch chỉ là WARN.')
    opt = ap.parse_args()

    dirs = list(opt.problem_dirs)
    if opt.all:
        dirs += find_all_problems(opt.all, set(opt.only or []) or None)
    if not dirs:
        die('no problem dirs given (positional args or --all ROOT)')

    testlib_h = ensure_testlib(opt.testlib)
    testlib_dir = os.path.dirname(os.path.abspath(testlib_h))

    reports = []
    for pdir in dirs:
        print('\n== %s ==' % pdir)
        reports.append(validate_problem(pdir, opt, testlib_dir))

    # ---- summary ----
    print('\n' + '=' * 74)
    order = {'FAIL': 0, 'WARN': 1, 'PASS': 2}
    npass = sum(r['status'] == 'PASS' for r in reports)
    nwarn = sum(r['status'] == 'WARN' for r in reports)
    nfail = sum(r['status'] == 'FAIL' for r in reports)
    for r in sorted(reports, key=lambda r: (order[r['status']], r['problem'])):
        print('  [%-4s] %-45s %2d fail, %2d warn, checker max %.2fs'
              % (r['status'], r['problem'][:45], len(r['failures']), len(r['warnings']), r['max_checker_wall']))
    print('-' * 74)
    print('  %d PASS   %d WARN (đọc tay trước khi tin)   %d FAIL (KHÔNG đưa vào manifest)'
          % (npass, nwarn, nfail))

    if opt.json:
        with open(opt.json, 'w', encoding='utf-8') as f:
            json.dump(reports, f, ensure_ascii=False, indent=2)
        print('  JSON report -> %s' % opt.json)

    sys.exit(1 if nfail else 0)


if __name__ == '__main__':
    main()
