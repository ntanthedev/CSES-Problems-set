#include <iostream>
#include <vector>
#include <stack>
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

static bool build(int pos, const vector<int>& input, vector<int>& assignment) {
    int n = (int)input.size();
    if (pos == n) return simulate(input, assignment);
    for (int st = 1; st <= 2; st++) {
        assignment[pos] = st;
        if (build(pos + 1, input, assignment)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> input(n);
    for (int i = 0; i < n; i++) cin >> input[i];

    vector<int> assignment(n);
    if (!build(0, input, assignment)) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << assignment[i];
    }
    cout << '\n';
}
