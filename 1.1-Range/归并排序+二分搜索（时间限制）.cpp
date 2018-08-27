// #include <iostream>
/* printf/scanf快于cin/cout */
#include <cstdio> 
using namespace std;

void merge(int* points, int lo, int mi, int hi) {
    int lb = mi - lo;
    int lc = hi - mi;
    int* A = points + lo;
    int* B = new int[lb];
    // for(int i = 0; i <lb; B[i++] = A[i])
    /* 勿滥用++/--，以防副作用和未定义行为 */
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    int* C = points + mi;

    for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
        if ((j < lb) && ((B[j] <= C[k]) || (lc <= k)))
            A[i++] = B[j++];
        if ((k < lc) && ((C[k] < B[j]) || (lb <= j)))
            A[i++] = C[k++];
    }

    delete[] B;
}

void mergeSort(int* points, int lo, int hi) {
    if (hi - lo < 2)
        return;
    else {
        int mi = (lo + hi) >> 1;
        mergeSort(points, lo, mi);
        mergeSort(points, mi, hi);
        merge(points, lo, mi, hi);
    }
}

int binSearch(int* points, int lo, int hi, int val) {
    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        if (val < points[mi])
            hi = mi;
        else
            lo = mi + 1;
    }
    return --lo;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int* points = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", points + i);
    mergeSort(points, 0, n);

    // int* results = new int[m];
    /* 及时输出即可。命令行交互不是调试的唯一途径 */
    for (int i = 0; i < m; i++) {
        int left, right;
        scanf("%d %d", &left, &right);

        /* left 和 right 大小相近时能否改进？ */
        int posi_l, posi_r;
        posi_l = binSearch(points, 0, n, left);
        
        // posi_r = binSearch(points, 0, n, right);
        /* 充分利用中间变量 */
        posi_r = binSearch(points, posi_l, n, right);
        
        int fix = 0;
        if (posi_l != -1) { // 开销相同时代码语义尽量明确，不要炫技（比如利用“短路原则”省略if等）
            if (points[posi_l] == left)
                fix = 1;
        } // 直接针对特殊情况寻找误差来源。利用大量测试用例枚举、归纳吃力不讨好 
        printf("%d\n", posi_r - posi_l + fix);
    }
    delete[] points; // delete[]在删除没有析构函数的基本数据结构时是O(1)操作

    return 0;
}
