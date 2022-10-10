#include <iostream>
using namespace std;

struct node
{
    char info;
    struct node *l, *r;
};
struct node *x, *z;

typedef struct node *itemType;

// Stack implementation with linked list
class Stack
{
private:
    struct stack_node
    {
        itemType data;
        struct stack_node *link;
    };

    struct stack_node *top;

public:
    Stack()
    {
        top = NULL;
    }
    ~Stack()
    {
        delete top;
    }
    inline void push(itemType v)
    {
        struct stack_node *temp = new struct stack_node;
        temp->data = v;
        temp->link = top;
        top = temp;
    }
    inline itemType pop()
    {
        struct stack_node *temp;
        itemType ret;
        if (empty())
        {
            std::cout << "stack underflow" << std::endl;
            return NULL;
        }
        temp = top;
        ret = temp->data;
        top = top->link;
        return ret;
    }
    inline int empty()
    {
        return top == NULL;
    }
};

// Queue implementation with linked list
class Queue
{
private:
    struct queue_node
    {
        itemType data;
        struct queue_node *next;
    };

    struct queue_node *head, *tail;

public:
    Queue()
    {
        head = NULL;
        tail = NULL;
    }
    ~Queue()
    {
        delete head;
        delete tail;
    }
    void put(itemType v)
    {
        struct queue_node *temp = new struct queue_node;
        temp->data = v;
        if (tail == NULL)
        {
            head = tail = temp;
            return;
        }
        tail->next = temp;
        tail = temp;
    }

    itemType get()
    {
        if (head == NULL)
            return NULL;

        struct queue_node *temp;
        itemType ret;
        temp = head;
        ret = temp->data;
        head = head->next;

        if (head == NULL)
            tail = NULL;
        delete temp;
        return ret;
    }

    int empty()
    {
        return head == NULL;
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

void levelOrderTraverse(struct node *t)
{
    Queue queue;
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

int main()
{
    char c;
    Stack stack;
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
