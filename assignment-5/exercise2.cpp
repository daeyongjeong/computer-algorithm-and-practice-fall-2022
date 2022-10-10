#include <iostream>
using namespace std;

struct node
{
    char info;
    struct node *l, *r;
};
struct node *x, *z;

typedef struct node *itemType;

class Stack
{
private:
    itemType *stack;
    int p;

public:
    Stack(int max = 100)
    {
        stack = new itemType[max];
        p = 0;
    }
    ~Stack()
    {
        delete stack;
    }
    inline void push(itemType v)
    {
        stack[p++] = v;
    }
    inline itemType pop()
    {
        return stack[--p];
    }
    inline int empty()
    {
        return !p;
    }
};

class Queue
{
private:
    itemType *queue;
    int head, tail;
    int size;

public:
    Queue(int max = 100)
    {
        queue = new itemType[max];
        size = max;
        head = 0, tail = 0;
    }
    ~Queue()
    {
        delete queue;
    }
    void put(itemType v)
    {
        queue[tail++] = v;
        if (tail > size)
            tail = 0;
    }

    itemType get()
    {
        itemType t = queue[head++];
        if (head > size)
            head = 0;
        return t;
    }

    int empty()
    {
        return head == tail;
    }
};

void visit(struct node *t)
{
    cout << t->info << ' ';
}

void levelOrderTraverse(struct node *t)
{
    Queue queue(50);
    queue.put(t);
    while (!queue.empty())
    {
        t = queue.get();
        visit(t);
        if (t->l != z)
            queue.put(t->l);
        if (t->r != z)
            queue.put(t->r);
    }
}

void traverse(struct node *t)
{
    if (t != z)
    {
        traverse(t->l);
        visit(t);
        traverse(t->r);
    }
}

int main()
{
    char c;
    Stack stack(50);

    z = new struct node;
    z->l = z;
    z->r = z;
    while ((c = cin.get()) != '\n')
    {
        while (c == ' ')
            cin.get(c);
        x = new struct node;
        x->info = c;
        x->l = z;
        x->r = z;
        if (c == '+' || c == '*')
        {
            x->r = stack.pop();
            x->l = stack.pop();
        }
        stack.push(x);
    }
    struct node *root = stack.pop();
    levelOrderTraverse(root);
}