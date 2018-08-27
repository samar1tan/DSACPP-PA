/* 参考了：https://github.com/xtaq/algorithms/blob/master/binarytree.cpp */

#include <cstdio>

#define MAX 4000001 // 输入限制400000，+1即可

int pre[MAX];
int post[MAX];
int in[MAX]; 
int n; // 加快速度，简化符号，把精力集中在算法实现上

void convert(int l1, int r1, int l2, int r2) { // 边界是序列的基本参数；pre = [l1, r1], post = [l2, r2]
	if (l1 == r1) {
		printf("%d ", pre[l1]); // 核心约定为pre，而不是post
		return;
	}
	else {
		int i;
		for (i = l2; pre[l1 + 1] != post[i]; i++); // 在post中找左子树根节点
		// 想清楚post的作用：为pre的划分找到边界

		/********** 如何加快实现算法的速度？ **********
		 * 1. 不变性：明确划分子问题；                *
		 * 2. 单调性：准确修正参数；                  *
		 * 3. 快速迭代：先满足基本要求，再考虑优化     *
		 * 4. 盲目调试不可取                         *
		 ********************************************/ 

		/* 按中序减而治之：左子树 -> 根节点 -> 右子树 */
		convert(l1 + 1, l1 + 1 + i - l2, l2, i); // l1加一，去掉原根节点；左子树长度是i - l2 + 1
		printf("%d ", pre[l1]);
		convert(l1 + 2 + i - l2, r1, i + 1, r2 - 1); // 右子树在pre上位于左子树右侧
	}
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", pre + i);
	for (int i = 0; i < n; i++)
		scanf("%d", post + i);

	convert(0, n - 1, 0, n - 1); // 注意边界值
	
	return 0;
}
