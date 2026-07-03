#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cost[i][j] = inf.readInt();
    }

    long long optimal = ans.readInt();
    int claimed_cost = ouf.readInt();
    if ((long long)claimed_cost != optimal)
        quitf(_wa, "Minimum total cost is %lld, got %d", optimal, claimed_cost);

    vector<int> emp_of_task(n, 0);
    vector<int> task_of_emp(n, 0);
    long long total = 0;

    for (int i = 0; i < n; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Employee %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "Task %d out of range", b);
        if (task_of_emp[a - 1] != 0)
            quitf(_wa, "Employee %d assigned more than one task", a);
        if (emp_of_task[b - 1] != 0)
            quitf(_wa, "Task %d assigned to more than one employee", b);
        task_of_emp[a - 1] = b;
        emp_of_task[b - 1] = a;
        total += cost[a - 1][b - 1];
    }

    if (total != optimal)
        quitf(_wa, "Claimed total cost %d, but actual sum of assignments is %lld",
              claimed_cost, total);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal assignment with total cost %lld", total);
}
