#include <iostream>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    multiset<int> left, right;
    ll left_sum = 0, right_sum = 0;

    auto fix = [&] {
        if (left.size() > right.size() + 1) {
            auto v = *left.rbegin();
            left_sum -= v;
            right_sum += v;
            right.insert(v);
            left.erase(left.find(v));
        }
        if (right.size() > left.size()) {
            auto v = *right.begin();
            right_sum -= v;
            left_sum += v;
            left.insert(v);
            right.erase(right.find(v));
        }
    };

    auto add = [&](int v) {
        if (!left.empty() && *left.rbegin() > v) {
            left.insert(v);
            left_sum += v;
        } else {
            right.insert(v);
            right_sum += v;
        }
        fix();
    };

    auto rem = [&](int v) {
        if (*left.rbegin() >= v) {
            left.erase(left.find(v));
            left_sum -= v;
        } else {
            right.erase(right.find(v));
            right_sum -= v;
        }
        fix();
    };

    auto cost = [&] {
        ll median = *left.rbegin();
        ll left_cost = left.size() * median - left_sum;
        ll right_cost = right_sum - right.size() * median;
        return left_cost + right_cost;
    };

    for (int i = 0; i < n; i++) {
        add(x[i]);
        if (i >= k) {
            rem(x[i - k]);
        }
        if (i >= k - 1) {
            cout << cost() << " ";
        }
    }
    cout << "\n";
}
