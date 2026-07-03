/*
 * ============================================================================
 *  CANONICAL TESTLIB CHECKER SKELETON  (DMOJ/VNOJ "bridged" + "testlib")
 * ============================================================================
 *  This file COMPILES AS-IS. It checks a toy problem:
 *      "Given n, print k (the minimum possible, taken from ans) followed by
 *       any permutation of 1..n."
 *  Replace the marked sections with the real problem's logic, but KEEP every
 *  defensive idiom — each one exists because a real generated checker shipped
 *  the corresponding bug class (see CHECKER_STRATEGY_V2.md §3).
 *
 *  HEADER CONTRACT (fill this in for every generated checker — reviewers rely
 *  on it):
 *    Problem:      <CSES id + name>
 *    Input read:   <exact fields read from inf, in order>
 *    Validity:     <every rule enforced on ouf>
 *    Optimality:   <which scalar(s) are compared against ans, or "bound only">
 *    Complexity:   <time / memory, must be <= O((n+m) log) / O(n+m)>
 * ============================================================================
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/* ---------------------------------------------------------------------------
 * SAFE SENTINEL HANDLING (kills bug class #2: unsafe stoi/stoll/atoi)
 *
 * Many problems allow "IMPOSSIBLE" / "NO" / "-1" as an answer. NEVER read a
 * token and stoi() it — a contestant printing "abc" or a 40-digit number
 * must get WA/PE, not crash the judge. Decide from `ans` FIRST, then read
 * `ouf` with the type you now know to expect. testlib's bounded readers do
 * all format+range validation and quit with _pe/_wa on their own.
 * ------------------------------------------------------------------------- */
static bool ansIsSentinel(const string &sentinel) {
    // Peek ans's first token without consuming checker state we still need:
    // simplest robust pattern — read it once, remember it.
    // (ans is trusted jury data; a plain readToken is fine here.)
    string t = ans.readToken();
    return t == sentinel;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    /* --- 1. Read the INPUT (inf) -----------------------------------------
     * inf is TRUSTED. Plain readInt()/readToken(), no bounds needed, and no
     * strict EOL checks (inf.readEoln() causes false jury errors on CRLF).
     *
     * GRID RULE (kills bug class #1, line-drift): NEVER inf.readLine() after
     * inf.readInt() — readInt does not consume the trailing '\n', so the
     * first readLine() returns "" and every row shifts. Read grid rows with
     * readToken(), which skips whitespace first:
     *     int n = inf.readInt(), m = inf.readInt();
     *     vector<string> g(n);
     *     for (int i = 0; i < n; i++) g[i] = inf.readToken();   // NOT readLine
     * ------------------------------------------------------------------- */
    int n = inf.readInt();

    /* --- 2. Decide the answer SHAPE from ans, then read ouf ---------------
     * If the problem has no IMPOSSIBLE case, delete this block and read
     * numbers directly.
     * ------------------------------------------------------------------- */
    const string SENT = "IMPOSSIBLE";           // or "-1", "NO", ...
    if (ansIsSentinel(SENT)) {
        // Jury says no solution exists -> contestant must agree.
        string tok = ouf.readToken();
        if (tok != SENT)
            quitf(_wa, "jury answer is %s but contestant printed \"%s\" "
                       "(claims a solution exists)", SENT.c_str(), compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported %s", SENT.c_str());
    }
    // ans is NOT the sentinel: its first token was already consumed by
    // ansIsSentinel() above -> it is the optimal scalar. Re-parse it:
    // (ansIsSentinel returned false, so re-read pattern: store token there
    //  in a global if you need the value; here we re-open via the remembered
    //  string. For clarity in real checkers, inline the peek:
    //      string atok = ans.readToken();
    //      if (atok == SENT) { ... } else { long long kAns = stoll(atok); }
    //  stoll on ANS is safe — ans is trusted jury data, ouf is not.)

    /* --- 3. Read the contestant's OUTPUT (ouf) with BOUNDED readers -------
     * EVERY numeric read from ouf MUST carry explicit bounds + a name:
     *     int k  = ouf.readInt(1, n, "k");
     *     long long c = ouf.readLong(0LL, 4'000'000'000'000LL, "cost");
     * This single idiom simultaneously kills:
     *   - bug class #2 (garbage token -> testlib itself quits _pe, no crash)
     *   - bug class #5 (k = 2e9 -> _wa BEFORE you ever allocate vector(k))
     *   - silent long-long overflow on absurd 20-digit tokens (_pe)
     * NEVER ouf.readInt() with no arguments. NEVER allocate anything sized
     * by a contestant number before that number passed a bounded read.
     * ------------------------------------------------------------------- */
    int k = ouf.readInt(1, n, "k");             // bounds BEFORE allocation
    vector<int> p(k);                            // safe: k <= n already proven
    vector<char> seen(n + 1, 0);
    for (int i = 0; i < k; i++) {
        p[i] = ouf.readInt(1, n, format("p[%d]", i + 1).c_str());
        if (seen[p[i]])
            quitf(_wa, "value %d appears twice (position %d)", p[i], i + 1);
        seen[p[i]] = 1;
    }

    /* --- 4. Optimality: compare SCALARS against ans, never recompute -------
     * Read the optimum (k, cost, length, ...) from ans and require equality.
     * NEVER re-implement max-flow / MCMF / suffix arrays / brute force in a
     * checker (bug class #3: checker TLE). Lightweight VERIFICATION of the
     * contestant's claimed structure (simulate their path, check their edges
     * exist) is fine; SOLVING the problem again is not.
     *
     * If the statement says "any answer with k <= BOUND", compare against the
     * BOUND from the statement, NOT against ans's k (bug class #4, e.g.
     * CSES 2427 Letter Pair Move Game).
     * ------------------------------------------------------------------- */
    // Example (ans layout: k on the first line, then a valid permutation):
    // int kAns = <ans's k, already peeked above>;
    // if (k != kAns) quitf(_wa, "not optimal: contestant k = %d, jury k = %d", k, kAns);

    /* --- 5. End-of-output: tolerate whitespace, reject junk ---------------
     * (kills bug class #6). EXACTLY this pattern:
     *   - NOT bare `ouf.seekEof();`   (return value ignored -> no-op)
     *   - NOT `ouf.readEof()`         (does not skip trailing whitespace)
     *   - NOT `ouf.readEoln()` anywhere on ouf (PE for a harmless blank line)
     * ------------------------------------------------------------------- */
    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");

    /* --- 6. Verdicts -------------------------------------------------------
     * ALWAYS quitf(_wa, ...) on failure. NEVER ensuref()/ensure() on
     * contestant data — they exit with code 3 ("assertion failed"), which the
     * DMOJ bridge does not show as WA. Messages must describe the
     * contestant's actual mistake, with indices/values, and must match the
     * branch (don't print "expected -1" in the branch where the CONTESTANT
     * printed -1 — that's the jury's line).
     * ------------------------------------------------------------------- */
    quitf(_ok, "valid permutation of size %d", k);
}
