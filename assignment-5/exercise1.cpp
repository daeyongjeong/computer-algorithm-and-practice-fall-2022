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

void visit(struct node *t)
{
    cout << t->info << ' ';
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
        x = new node;
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
    traverse(root);
}