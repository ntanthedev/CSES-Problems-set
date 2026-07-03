#include <iostream>
#include <stack>
#include <vector>
using namespace std;

static bool simulate(const vector<int>& input, const vector<int>& assignment) {
    stack<int> s1, s2;
    int next_output = 1;
    int input_pos = 0;
    int n = (int)input.size();

    while (next_output <= n) {
        if (!s1.empty() && s1.top() == next_output) {
            s1.pop();
            next_output++;
            continue;
        }
        if (!s2.empty() && s2.top() == next_output) {
            s2.pop();
            next_output++;
            continue;
        }
        if (input_pos >= n) return false;

        int val = input[input_pos];
        int st = assignment[input_pos++];
        if (st == 1) {
            if (!s1.empty() && val > s1.top()) return false;
            s1.push(val);
        } else {
            if (!s2.empty() && val > s2.top()) return false;
            s2.push(val);
        }
    }
    return true;
}

static int drainCount(stack<int> s1, stack<int> s2, int next_out) {
    while (true) {
        if (!s1.empty() && s1.top() == next_out) {
            s1.pop();
            next_out++;
            continue;
        }
        if (!s2.empty() && s2.top() == next_out) {
            s2.pop();
            next_out++;
            continue;
        }
        break;
    }
    return next_out;
}

static bool build(int pos, const vector<int>& input, vector<int>& assignment) {
    int n = (int)input.size();
    if (pos == n) return simulate(input, assignment);
    for (int st = 1; st <= 2; st++) {
        assignment[pos] = st;
        if (build(pos + 1, input, assignment)) return true;
    }
    return false;
}

static bool greedy(const vector<int>& input, vector<int>& assignment) {
    stack<int> s1, s2;
    int next_out = 1;

    auto drain = [&]() {
        while (true) {
            if (!s1.empty() && s1.top() == next_out) {
                s1.pop();
                next_out++;
                continue;
            }
            if (!s2.empty() && s2.top() == next_out) {
                s2.pop();
                next_out++;
                continue;
            }
            break;
        }
    };

    for (int i = 0; i < (int)input.size(); i++) {
        int val = input[i];
        bool ok1 = s1.empty() || val < s1.top();
        bool ok2 = s2.empty() || val < s2.top();

        if (!ok1 && !ok2) return false;

        if (ok1 && ok2) {
            stack<int> t1 = s1, t2 = s2;
            t1.push(val);
            int d1 = drainCount(t1, t2, next_out);
            t1 = s1;
            t2 = s2;
            t2.push(val);
            int d2 = drainCount(t1, t2, next_out);
            if (d1 >= d2) {
                assignment[i] = 1;
                s1.push(val);
            } else {
                assignment[i] = 2;
                s2.push(val);
            }
        } else if (ok1) {
            assignment[i] = 1;
            s1.push(val);
        } else {
            assignment[i] = 2;
            s2.push(val);
        }
        drain();
    }

    drain();
    return next_out == (int)input.size() + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> input(n);
    for (int i = 0; i < n; i++)
        cin >> input[i];

    vector<int> assignment(n);
    bool ok = n <= 20 ? build(0, input, assignment) : greedy(input, assignment);

    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (i)
            cout << ' ';
        cout << assignment[i];
    }
    cout << '\n';
    return 0;
}
