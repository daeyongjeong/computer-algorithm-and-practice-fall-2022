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

int main()
{
    const int N = 10000;
    infoType data[N];
    BST T1(N);

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

    for (int i = 0; i < N; i++)
        T1.BSTsearch(data[i]);

    cout << "Search T1" << endl;
    cout << "  Total comparisons\t" << comparisons << endl;
    cout << "  Average comparisons\t" << comparisons / N << endl;
}