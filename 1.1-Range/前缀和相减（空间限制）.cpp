/* 输入限定为不大于10^7的非负整数，内存限制足够大为256MB
 * 此解法时间开销优于归并排序+二分搜索
 */

#define N 10000000

#include <cstdio>
using namespace std;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    // int axis[N];
    /* 堆的容量大于栈 */
    int* axis = new int[N + 1]; // [0, 10000000]
    for (int i = 0; i < N; i++) // memset()的速度没有优势
        axis[i] = 0;

    for (int i = 0, dot; i < n; i++) {
        scanf("%d", &dot);
        axis[dot]++; // 表明这个位置有输入的数字
    }

    for (int i = 1; i <= N; i++)
        axis[i] += axis[i - 1]; // 元素值为其自身以及前缀中所包含的输入数字的个数

    for (int i = 0, left, right; i < m; i++) { // O(1)的查询操作
        scanf("%d %d", &left, &right);
        if (left) 
            printf("%d\n", axis[right] - axis[left - 1]); // 不论left处存值与否
        else
            printf("%d\n", axis[right]); // left为0，特殊处理，此时可只看right
    }

    return 0;
}
