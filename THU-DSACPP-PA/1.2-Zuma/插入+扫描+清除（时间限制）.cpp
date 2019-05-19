#include <cstdio>

const int SIZE = 1 << 21;   
struct fast_io{
    char inbuf[SIZE];  
    char outbuf[SIZE];  
    fastio(){  
        setvbuf(stdin, inbuf, _IOFBF, SIZE);  
        setvbuf(stdout, outbuf, _IOFBF, SIZE);  
    }  
} io; // 通过增大缓冲区加速I/O(https://blog.csdn.net/weixin_37656939/article/details/76152550)

struct node {
    char col;
    
    node* next;
    node* prev;
};

struct list{
    int _size;
    node* _head;
    node* _tail;

    list();
    // ~list(); // 时间限制
    // void insert(char, int);
    void insertAsLast(char); // 列表的顺序插入较之随机插入可更高效
    void insertAndClean(char, int); // insertAfterClean()会更快吗？
    void print();
};

inline list::list() {
    _size = 0;

    _head = new node;
    _head->col = '0';

    _tail = new node;
    _tail->col = '0';

    _head->next = _tail;
    _tail->prev = _head;
    _head->prev = NULL;
    _tail->next = NULL;
}

inline void list::insertAsLast(char col) {
    node* raw = new node;
    raw->col = col;

    _tail->prev->next = raw;
    raw->prev = _tail->prev;
    raw->next = _tail;
    _tail->prev = raw;
    _size++; 
}

inline void list::insertAndClean(char col, int rank) {
    node* raw = new node;
    raw->col = col;

    node* handle;
    if(rank <= _size / 2) {
        handle = _head;
        for (int i = 0; i < rank; i++)
            handle = handle->next;    
    }
    else {
        handle = _tail;
        for (int i = _size; i >= rank; i--)
            handle = handle->prev;
    }
    node* temp = handle->next;
    handle->next = raw;
    raw->prev = handle;
    raw->next = temp;
    temp->prev = raw;
    handle = raw;
    _size++;

    int count =	1;
    node* anchor_l = handle;
    node* anchor_r = handle; // 变量取名时取得差异大一些，可能更不容易弄混
    while(_size > 2) {
        while (anchor_l->col == anchor_l->prev->col) {
            count++;
            anchor_l = anchor_l->prev;
        }
        
        while (anchor_r->col == anchor_r->next->col) {
            count++;
            anchor_r = anchor_r->next;
        }

        if (count < 3) 
            break;
        else {
            // handle = anchor_l->next;
            // for (int i = 0; i < count; i++) {
                // node* temp = handle;
                // handle = handle->next;
                // delete temp;
                // _size--;
            // } // 时间限制
            anchor_l = anchor_l->prev;
        	anchor_r = anchor_r->next;
            anchor_l->next = anchor_r;
            anchor_r->prev = anchor_l;
            _size -= count;
            
            if (anchor_l->col != anchor_r->col)
                break;
            else
                count = 2;
        }
    }
}

inline void list::print() {
    if (!_size)
        printf("-\n");
    else {
        node* handle = _head->next;
        while (handle != _tail) {
            printf("%c", handle->col);
            handle = handle->next;
        }
        putchar('\n');
    }
}

int main() {
    list track;
    
    char temp;
    while(true) {
        scanf("%c", &temp);
        if (temp == '\n')
            break;
        else
        	track.insertAsLast(temp);
    };

    int n, rank;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &rank, &temp);
        track.insertAndClean(temp, rank);
        track.print();
    }

    return 0;
}
