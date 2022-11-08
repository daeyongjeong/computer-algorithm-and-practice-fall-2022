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

    void BSTInorderTraverse(node *t, BST *t2);

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
    void BSTInorderTraverse(BST *t2);
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

void BST::BSTInorderTraverse(BST *t2)
{
    BSTInorderTraverse(head->r, t2);
}

void BST::BSTInorderTraverse(node *t, BST *t2)
{
    if (t != z)
    {
        BSTInorderTraverse(t->l, t2);
        cout << t->key << '\t';
        t2->BSTinsert(t->key, t->key);
        BSTInorderTraverse(t->r, t2);
    }
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

    cout << "Inorder traverse and make new tree T2" << endl;
    T1.BSTInorderTraverse(&T2);
    cout << endl
         << endl;

    cout << "Search T2" << endl;
    for (int i = 0; i < N; i++)
        T2.BSTsearch(data[i]);

    cout << "  Total comparisons\t" << comparisons << endl;
    cout << "  Average comparisons\t" << comparisons / N << endl;
    comparisons = 0;
}