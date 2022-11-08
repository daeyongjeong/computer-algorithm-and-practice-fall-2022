#include <iostream>
#include <random>
using namespace std;

#define infoNIL -1
#define itemMIN -1

typedef int itemType;
typedef int infoType;
int comparisons = 0;

class BST
{
private:
    struct node
    {
        itemType key;
        infoType info;
        struct node *l, *r;

        node(itemType k, infoType i, struct node *ll, struct node *rr)
        {
            key = k;
            info = i;
            l = ll;
            r = rr;
        }
    };
    struct node *head, *z;

    int minimum();
    int maximum();
    int level(node *t);

public:
    BST(int max)
    {
        z = new node(0, infoNIL, 0, 0);
        head = new node(itemMIN, 0, z, z);
    }

    ~BST()
    {
        delete (z);
        delete (head);
    }

    infoType BSTsearch(itemType v);
    void BSTinsert(itemType v, infoType info);
    void MaxMinLvl();
};

infoType BST::BSTsearch(itemType v)
{
    struct node *x = head->r;
    z->key = v;
    while (v != x->key)
    {
        comparisons++;
        x = (v < x->key) ? x->l : x->r;
    }
    return x->info;
}

void BST::BSTinsert(itemType v, infoType info)
{
    struct node *p, *x;
    p = head;
    x = head->r;
    while (x != z)
    {
        p = x;
        x = (v < x->key) ? x->l : x->r;
    }
    x = new node(v, info, z, z);
    if (v < p->key)
        p->l = x;
    else
        p->r = x;
}

int BST::maximum()
{
    struct node *p, *x;
    p = head;
    x = head->r;
    while (x != z)
    {
        p = x;
        x = x->r;
    }
    return p->key;
}

int BST::minimum()
{
    struct node *p, *x;
    p = head;
    x = head->r;
    while (x != z)
    {
        p = x;
        x = x->l;
    }
    return p->key;
}

int BST::level(node *t)
{
    if (t != z)
        return max(level(t->l), level(t->r)) + 1;
    return -1;
}

void BST::MaxMinLvl()
{
    cout << "  Maximum\t" << maximum() << endl;
    cout << "  Minimum\t" << minimum() << endl;
    cout << "  Level\t\t" << level(head) << endl;
}

int main()
{
    const int N = 10000;
    infoType data[N];
    BST T1(N), T2(N);

    // C++ style random number generator
    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, N);

    cout << "Make new tree T1" << endl
         << endl;
    for (int i = 0; i < N; i++)
    {
        data[i] = dist(gen);
        T1.BSTinsert(data[i], i);
    }

    cout << "Max, Min, Level of T1" << endl;
    T1.MaxMinLvl();
}