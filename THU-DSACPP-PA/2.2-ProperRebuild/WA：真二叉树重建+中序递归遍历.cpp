/*********************************************
 * 警告：错误代码                             *
 * 本地小规模用例测试过关，但OJ上20个用例17个WA *
 * *******************************************/


#include <cstdio>

struct tnode {
    int no;
    tnode* prt;
    tnode* lChd;
    tnode* rChd;
};

struct btree {
    tnode* root;
    
    btree();
    tnode* insertLC(tnode*, int);
    tnode* insertRC(tnode*, int);
    void reconstruct(tnode*, int*, int*, int n);
    void printInorder(tnode*);
};

inline btree::btree() {
    root = new tnode;
    root->prt = root->lChd = root->rChd = NULL;
    root->no = 1;
}

inline tnode* btree::insertLC(tnode* parent, int index) {
    tnode* raw = new tnode;
    raw->prt = parent;
    parent->lChd = raw;
    raw->lChd = raw->rChd = NULL;
    raw->no = index;

    return raw;
}

inline tnode* btree::insertRC(tnode* parent, int index) {
    tnode* raw = new tnode;
    raw->prt = parent;
    parent->rChd = raw;
    raw->lChd = raw->rChd = NULL;
    raw->no = index;

    return raw;
}

/********************************疑似错误来源********************************/
inline void btree::reconstruct(tnode* origin, int* pre, int* post, int n) {
    if (n == 1)
        return;
    else {
        int lc = pre[1];
        int rc = post[n - 2];
        tnode* lo = insertLC(origin, lc);
        tnode* ro = insertRC(origin, rc);
        
        int r;
        for (r = 2; pre[r] != rc; r++);
        int l = r - 2;
        reconstruct(lo, pre + 1, post, r - 1);
        reconstruct(ro, pre + r, post + l + 1, n - r);

        return;
    }
}
/**************************************************************************/

inline void btree::printInorder(tnode* origin) { // 将计算流程直接“翻译”成代码，递归地分而治之
    if (origin == NULL) // 触底
        return; // 返回
    else {
        printInorder(origin->lChd);
        printf("%d ", origin->no);
        printInorder(origin->rChd);
    }
}

int main() {
    int n; // 节点总数
    scanf("%d", &n);
    
    btree prop;
    int* preorder = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", preorder + i);
    int* postorder = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", postorder + i);

    prop.reconstruct(prop.root, preorder, postorder, n);
    delete[] preorder;
    delete[] postorder;

    prop.printInorder(prop.root);

    return 0;
}
