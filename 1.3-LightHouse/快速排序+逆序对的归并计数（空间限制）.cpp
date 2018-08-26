#include <cstdio>
#include <cstdlib>

const int SZ = 1 << 20;
struct fastio {
    char inbuf[SZ];
    char outbuf[SZ];
    fastio() {
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
} io;

struct point {
    int x;
    int y;
};

int partition(point* pnt, int lo, int hi) {
    // point cnd = pnt[lo]; // 不要对基本类型的赋值与等号习以为常，自定义类型不一定有构造函数，也不一定重载了等号
    point cnd; // 候选轴点的备份
    cnd.x = pnt[lo].x;
    cnd.y = pnt[lo].y;

    /* 一达到lo==hi，循环就不再进行实际操作 */
    while (lo < hi) {
        // while(lo < hi && cnd.x < pnt[hi].x) // 为了准确还原算法思路中的分支走向，谨慎使用复合跳出条件
        while (lo < hi) {
            if (cnd.x < pnt[hi].x)
                hi--;
            else {
                // pnt[lo++] = pnt[hi]; // 同第62行之理
                pnt[lo].x = pnt[hi].x;
                pnt[lo++].y = pnt[hi].y;
                break;
            }
        }

        while (lo < hi) {
            // if (pnt[hi].x < cnd.x) // 对称还是相同？
            if(pnt[lo].x < cnd.x)
                lo++;
            else {
                pnt[hi].x = pnt[lo].x;
                pnt[hi--].y = pnt[lo].y;
                break;
            }
        }
    }

    pnt[lo].x = cnd.x;
    pnt[lo].y = cnd.y;
    return lo;
}

void quickSort(point* pnt, int lo, int hi) {
    if (hi - lo < 2)
        return;
    else {
        int pivot = partition(pnt, lo, hi - 1); // 在[lo, hi-1]内选取轴点
        quickSort(pnt, lo, pivot);
        quickSort(pnt, pivot + 1, hi); // 空开轴点，需要加一
    }
}

/* 改造了归并排序算法，在排序的同时计算顺序对数目
 * 参考资料：“习题辅导：LightHouse”
 */
long int ordBetween(int* vec, int lo, int mi, int hi) { // 预防数据上溢
    int* A = vec + lo;
    int lb = mi - lo;
    int B[lb]; // GCC允许（MSVC不允许）在栈上声明动态数组（可能导致Stack Overflow，后果自负）。可用于规避OJ的（堆）内存限制。
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    int* C = vec + mi;
    int lc = hi - mi;

    long int count = 0;
    for (int i = 0, j = 0, k = 0; j < lb || k < lc; ) {
        if (j < lb && (k >= lc || B[j] < C[k])) { // 不会相等 
            A[i++] = B[j++];
            count += (lc - k);
        }
        if (k < lc && (j >= lb || C[k] < B[j]))
            A[i++] = C[k++];
        // count += (lb - j); // 虽然相对大小不定，但是与其计算逆序对再换算，不如直接计算顺序对
    }

    return count;
}

long int ord(int* vec, int lo, int hi) {
    if (hi - lo < 2)
        return 0;
    else {
        int mi = (lo + hi) >> 1;
        long int lord = ord(vec, lo, mi); // 预防数据上溢
        long int rord = ord(vec, mi, hi);
        long int order = lord + rord + ordBetween(vec, lo, mi, hi);
        return order;
    }
}

int main() {
    int n; // 灯塔总数
    scanf("%d", &n);
    point* points = new point[n];
    for (int i = 0; i < n; i++)
        scanf("%d %d", &(points[i].x), &(points[i].y));

    quickSort(points, 0, n);
    int* ys = new int[n];
    for(int i = 0; i < n; i++)
    	ys[i] = points[i].y;
    delete[] points; // 及时回收内存

    long int lighted = ord(ys, 0, n); // 除了结果，每个中间变量也需要预防数据溢出
    printf("%ld\n", lighted);

    return 0;
}
