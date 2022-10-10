#include <iostream>

typedef int itemType;

class Stack2
{
public:
    Stack2()
    {
        head = NULL;
        z = NULL;
    }

    ~Stack2()
    {
        delete head, z;
    }

    void push(itemType v)
    {
        z = new node;
        z->key = v;
        z->next = head;
        head = z;
    }

    itemType pop()
    {
        if (empty())
            return -1;

        itemType v = head->key;
        z = head;
        head = head->next;
        delete z;
        return v;
    }

    int empty()
    {
        return (head == NULL);
    }

private:
    struct node
    {
        itemType key;
        struct node *next;
    };
    struct node *head, *z;
};

int main()
{
    char c;
    Stack2 acc;
    int x;
    while ((c = std::cin.get()) != '\n')
    {
        x = 0;
        while (c == ' ')
            std::cin.get(c);
        if (c == '+')
            x = acc.pop() + acc.pop();
        if (c == '-')
            x = acc.pop() - acc.pop();
        if (c == '*')
            x = acc.pop() * acc.pop();
        if (c == '/')
            x = acc.pop() / acc.pop();
        while (c >= '0' && c <= '9')
        {
            x = 10 * x + (c - '0');
            std::cin.get(c);
        }
        acc.push(x);
    }
    std::cout << acc.pop() << '\n';
}