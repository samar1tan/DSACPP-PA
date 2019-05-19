#include <cstdio>

struct stack {
    int _size, _capacity;
    int* top;

    stack(int);
    int push(int);
    int pop();
};

inline stack::stack(int cap) {
    int* bottom = new int[cap + 1];
    *bottom = -1;
    top = bottom;
    _size = 0;
    _capacity = cap;
}

inline int stack::push(int num) {
    if (_size == _capacity)
        return -1;
    else {
        top++;
        *top = num;
        _size++;

        return 0;
    }
}

inline int stack::pop() {
    if (_size == 0)
        return -1;
    else {
        int bak = *top;
        top--;
        _size--;

        return bak;
    }
}

int main() {
    int n, m; // 输入n，驻留m
    scanf("%d %d", &n, &m);
    
    int* aim = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", aim + i);

    stack A(n); // 利用栈混洗进行模拟
    for (int i = n; i >= 1; i--)
        A.push(i);
    stack B(m);

    int* oprt = new int[2 * n]; // (push + pop) * n || NO

    #define PUSH 0
    #define POP 1

    int i = 0;
    for(int j = 0; i < n; i++) {
        while (A._size > 0 && *(A.top) <= aim[i]) { // 贪心
            if (B.push(A.pop()) == -1)
                break;
            else
                oprt[j++] = PUSH;
        }
        int temp = B.pop();
        if (temp == -1 || temp != aim[i])
            break;
        else {
            oprt[j++] = POP;
        }
    }

    if (i < n) 
        printf("No\n");
    else {
        for (int i = 0; i < (2 * n); i++) {
            if (oprt[i])
                printf("pop\n");
            else
                printf("push\n");
        }
    }

    return 0;
}
