#include <iostream>

typedef int itemType;

class Stack1
{
private:
    itemType *stack;
    int p;

public:
    Stack1(int max = 100)
    {
        stack = new itemType[max];
        p = 0;
    }

    ~Stack1()
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

int main()
{
    char c;
    Stack1 acc(50);
    int x;
    while ((c = std::cin.get()) != '\n')
    {
        x = 0;
        while (c == ' ')
            std::cin.get(c);
        if (c == '+')
            x = acc.pop() + acc.pop();
        if (c == '*')
            x = acc.pop() * acc.pop();
        while (c >= '0' && c <= '9')
        {
            x = 10 * x + (c - '0');
            std::cin.get(c);
        }
        acc.push(x);
    }
    std::cout << acc.pop() << '\n';
}
