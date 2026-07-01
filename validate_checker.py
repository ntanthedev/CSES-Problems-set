#!/usr/bin/env python3
"""
Local sanity-checker for a testlib.h checker.cpp before it ever touches the OJ.

A buggy checker is dangerous in a specific way: it fails *silently*. It won't
throw an error on upload - it'll just quietly accept wrong answers (or reject
correct ones) forever, and nobody will notice until a student complains. This
script catches the two most common authoring bugs before that happens:

  1. Does the checker even compile?
  2. Does it accept the canonical judge answer (N.out) against itself?
     (fails => the checker's own logic is broken, e.g. wrong format assumptions)
  3. Does it accept solution.cpp's OWN output (usually different bytes than
     N.out for "multiple valid answer" problems - this is the whole point of
     writing a custom checker, so this is the most important test)
  4. Does it REJECT a couple of heuristically-corrupted outputs?
     (fails => the checker is too lenient / a no-op that accepts everything -
     the single most dangerous and hardest-to-notice bug in a checker)

This is a smoke test, not a proof. #4 especially is a heuristic - some
problems can legitimately accept a "corrupted" output (e.g. if the mutation
lands on an unconstrained value), so a warning there means "look at this by
hand", not necessarily "the checker is broken". Always skim the generated
checker.cpp yourself before trusting it in bulk.

USAGE
    pip install requests   # only needed for the first run (fetches testlib.h)
    python validate_checker.py PROBLEM_DIR [--cases N] [--testlib PATH]

    PROBLEM_DIR must contain (matching the CSES-Problems-set layout):
        checker.cpp
        solution.cpp
        tests_<ID>.zip        (N.in / N.out at the zip root)

EXIT CODE
    0  all checks passed (mutation-rejection is a warning, not a failure)
    1  compile error, or the checker failed a MUST-pass check (#2 or #3)
"""
import argparse
import glob
import os
import re
import shutil
import subprocess
import sys
import tempfile
import urllib.request
import zipfile

TESTLIB_URL = 'https://raw.githubusercontent.com/MikeMirzayanov/testlib/master/testlib.h'


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
        die('could not download testlib.h (%s). Pass --testlib /path/to/testlib.h instead.' % e)
    return path


def compile_cpp(src, out, extra_include_dir=None, std='c++17'):
    cmd = ['g++', '-O2', '-std=%s' % std, '-o', out, src]
    if extra_include_dir:
        cmd[1:1] = ['-I', extra_include_dir]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        die('compile failed for %s:\n%s' % (src, r.stderr[-4000:]))


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


def run(cmd, timeout=10):
    return subprocess.run(cmd, capture_output=True, timeout=timeout)


def mutate(judge_out):
    """A couple of cheap, generic corruptions. Returns a list of (label, bytes)."""
    text = judge_out.decode('utf-8', errors='replace')
    lines = text.splitlines()
    out = []

    # 1) bump the last integer token found anywhere in the output by 1
    m = list(re.finditer(r'-?\d+', text))
    if m:
        last = m[-1]
        bumped = text[:last.start()] + str(int(last.group()) + 1) + text[last.end():]
        out.append(('last integer +1', bumped.encode()))

    # 2) drop the last non-empty line entirely (truncated output)
    nonempty = [i for i, l in enumerate(lines) if l.strip()]
    if len(nonempty) >= 1:
        i = nonempty[-1]
        truncated = '\n'.join(lines[:i]) + '\n'
        out.append(('drop last line', truncated.encode()))

    # 3) reverse the token order of the last non-empty line (breaks pairing /
    #    ordering-sensitive answers; harmless no-op for genuinely order-free ones)
    if nonempty:
        i = nonempty[-1]
        toks = lines[i].split()
        if len(toks) >= 2:
            swapped = lines[:i] + [' '.join(reversed(toks))] + lines[i + 1:]
            out.append(('reverse last line tokens', ('\n'.join(swapped) + '\n').encode()))

    return out


def classify(returncode):
    # DMOJ 'testlib' bridged type: 0=AC, 1=WA, 2=PE, 3=assertion failed,
    # 7=partial (points on stderr). Treat anything != 0 (and != 7 w/ points==1.0) as "not AC".
    if returncode == 0:
        return 'AC'
    if returncode == 1:
        return 'WA'
    if returncode == 2:
        return 'PE'
    if returncode == 3:
        return 'ASSERT-FAIL'
    if returncode == 7:
        return 'PARTIAL'
    return 'ERROR(%d)' % returncode


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('problem_dir')
    ap.add_argument('--cases', type=int, default=5, help='How many test cases to sample (default 5).')
    ap.add_argument('--testlib', default=os.path.join(tempfile.gettempdir(), 'testlib.h'),
                    help='Path to testlib.h (downloaded automatically if missing).')
    opt = ap.parse_args()

    pdir = opt.problem_dir
    checker_src = os.path.join(pdir, 'checker.cpp')
    solution_src = os.path.join(pdir, 'solution.cpp')
    zips = glob.glob(os.path.join(pdir, 'tests_*.zip'))
    if not os.path.exists(checker_src):
        die('no checker.cpp in %s' % pdir)
    if not os.path.exists(solution_src):
        die('no solution.cpp in %s' % pdir)
    if not zips:
        die('no tests_*.zip in %s' % pdir)

    testlib_h = ensure_testlib(opt.testlib)
    workdir = tempfile.mkdtemp(prefix='checker_validate_')
    try:
        checker_bin = os.path.join(workdir, 'checker')
        solution_bin = os.path.join(workdir, 'solution')
        print('Compiling checker.cpp ...')
        compile_cpp(checker_src, checker_bin, extra_include_dir=os.path.dirname(testlib_h))
        print('Compiling solution.cpp ...')
        compile_cpp(solution_src, solution_bin)

        cases = read_cases(zips[0])
        if not cases:
            die('zip has no N.in/N.out pairs')
        sample = cases[:opt.cases]
        print('Testing against %d/%d case(s) from %s\n' % (len(sample), len(cases), os.path.basename(zips[0])))

        hard_fail = warn = 0
        for num, inp, judge_out in sample:
            in_f = os.path.join(workdir, '%d.in' % num)
            judge_f = os.path.join(workdir, '%d.judge.out' % num)
            open(in_f, 'wb').write(inp)
            open(judge_f, 'wb').write(judge_out)

            # --- run solution.cpp fresh on this input ---
            try:
                sol_r = subprocess.run([solution_bin], input=inp, capture_output=True, timeout=10)
                sol_out = sol_r.stdout
            except subprocess.TimeoutExpired:
                print('[case %d] solution.cpp TIMED OUT - skipping this case' % num)
                continue
            sol_f = os.path.join(workdir, '%d.sol.out' % num)
            open(sol_f, 'wb').write(sol_out)

            # --- MUST pass: judge output vs itself ---
            r = run([checker_bin, in_f, judge_f, judge_f])
            verdict = classify(r.returncode)
            ok = verdict in ('AC', 'PARTIAL')
            print('[case %d] judge-output self-check ......... %-12s %s' % (num, verdict, 'ok' if ok else 'FAIL'))
            if not ok:
                hard_fail += 1
                print('          stderr: %s' % r.stderr.decode(errors='replace')[:300])

            # --- MUST pass: solution.cpp's own output ---
            r = run([checker_bin, in_f, sol_f, judge_f])
            verdict = classify(r.returncode)
            ok = verdict in ('AC', 'PARTIAL')
            print('[case %d] solution.cpp output ............. %-12s %s' % (num, verdict, 'ok' if ok else 'FAIL'))
            if not ok:
                hard_fail += 1
                print('          stderr: %s' % r.stderr.decode(errors='replace')[:300])
                print('          (if solution.cpp genuinely differs from N.out and this fails, '
                      'the checker is rejecting a VALID alternate answer - the exact bug this test exists to catch)')

            # --- SHOULD fail: corrupted outputs ---
            any_rejected = False
            for label, bad in mutate(judge_out):
                bad_f = os.path.join(workdir, '%d.bad.out' % num)
                open(bad_f, 'wb').write(bad)
                r = run([checker_bin, in_f, bad_f, judge_f])
                verdict = classify(r.returncode)
                rejected = verdict not in ('AC', 'PARTIAL')
                any_rejected = any_rejected or rejected
                print('[case %d] mutation "%s" ....%s%-12s %s' % (
                    num, label, '.' * max(1, 18 - len(label)), verdict,
                    'rejected (good)' if rejected else 'ACCEPTED'))
            if not any_rejected:
                warn += 1
                print('          WARNING: no mutation was rejected for case %d - '
                      'either this case has no meaningful invariant to break, or the '
                      'checker is too lenient. Review by hand.' % num)
            print()

        print('=' * 70)
        if hard_fail:
            print('FAILED: %d hard failure(s) - do not add this checker to CHECKER_MANIFEST.json yet.' % hard_fail)
            sys.exit(1)
        elif warn:
            print('PASSED with %d warning(s) - skim the checker by hand before trusting it.' % warn)
        else:
            print('PASSED all checks.')
    finally:
        shutil.rmtree(workdir, ignore_errors=True)


if __name__ == '__main__':
    main()
