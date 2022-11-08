#include <iostream>
#include <random>

using namespace std;

class RedBlackTree
{
private:
    enum color
    {
        BLACK,
        RED
    };

    struct node
    {
        enum color color = BLACK;
        int key;
        struct node *left;
        struct node *right;
        struct node *p;

        node(int k, struct node *l, struct node *r, struct node *_p)
        {
            key = k;
            left = l;
            right = r;
            p = _p;
        }
    };

    struct node *root;
    struct node *nil;
    int comp = 0;

    void left_rotate(struct node *x);
    void right_rotate(struct node *y);

    void insert_fixup(struct node *z);

public:
    RedBlackTree()
    {
        nil = new node(-1, NULL, NULL, NULL);
        nil->left = nil;
        nil->right = nil;
        nil->p = nil;
        root = nil;
    }
    struct node *search(int k);
    int batch_search(vector<int> *k);

    void insert(int k);
};

class BinarySearchTree
{
private:
    struct node
    {
        int key;
        struct node *left = NULL;
        struct node *right = NULL;
        struct node *p = NULL;

        node(int k)
        {
            key = k;
        }
    };

    struct node *root = NULL;
    int comp = 0;

public:
    void inorder_tree_walk();
    void inorder_tree_walk(struct node *x);

    struct node *search(int k);
    int batch_search(vector<int> *k);

    void insert(int k);
    void batch_insert_from(vector<int> *k);
    void batch_insert_to(struct node *x, BinarySearchTree *t);
    void batch_insert_to(BinarySearchTree *t);
    void batch_insert_to(struct node *x, RedBlackTree *t);
    void batch_insert_to(RedBlackTree *t);
};

vector<int> *create_random_data(int n);
void print_key(int k);

/* main */

int main()
{
    const int N = 1000;
    vector<int> *random_data = create_random_data(N);

    BinarySearchTree t1;
    BinarySearchTree t2;
    RedBlackTree t3;
    int comp = 0;

    t1.batch_insert_from(random_data);

    cout << "T1 tree walk" << endl;
    t1.inorder_tree_walk();
    std::cout << '\n';

    cout << "T1 search" << endl;
    comp = t1.batch_search(random_data);
    cout << "Total comparisons\t" << comp << endl;
    cout << "Average comparisons\t" << comp / N << endl;

    t1.batch_insert_to(&t2);
    cout << "T2 search" << endl;
    comp = t2.batch_search(random_data);
    cout << "Total comparisons\t" << comp << endl;
    cout << "Average comparisons\t" << comp / N << endl;

    t1.batch_insert_to(&t3);
    cout << "T3 search" << endl;
    comp = t3.batch_search(random_data);
    cout << "Total comparisons\t" << comp << endl;
    cout << "Average comparisons\t" << comp / N << endl;
}

/* BinarySearchTree */

void BinarySearchTree::inorder_tree_walk()
{
    inorder_tree_walk(root);
}

void BinarySearchTree::inorder_tree_walk(struct node *x)
{
    if (x != NULL)
    {
        inorder_tree_walk(x->left);
        cout << ' ' << x->key;
        inorder_tree_walk(x->right);
    }
}

struct BinarySearchTree::node *BinarySearchTree::search(int k)
{
    struct node *x = root;
    while (x != NULL && k != x->key)
    {
        comp++;
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

int BinarySearchTree::batch_search(vector<int> *k)
{
    comp = 0;
    for (vector<int>::iterator it = k->begin(); it != k->end(); ++it)
        search(*it);
    return comp;
}

void BinarySearchTree::insert(int k)
{
    struct node *z = new node(k);
    struct node *y = NULL;
    struct node *x = root;

    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
        z->p = y;
    }

    if (y == NULL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

void BinarySearchTree::batch_insert_from(vector<int> *k)
{
    for (vector<int>::iterator it = k->begin(); it != k->end(); ++it)
    {
        insert(*it);
    }
}

void BinarySearchTree::batch_insert_to(BinarySearchTree *t)
{
    batch_insert_to(root, t);
}

void BinarySearchTree::batch_insert_to(struct node *x, BinarySearchTree *t)
{
    if (x != NULL)
    {
        batch_insert_to(x->left, t);
        t->insert(x->key);
        batch_insert_to(x->right, t);
    }
}
void BinarySearchTree::batch_insert_to(RedBlackTree *t)
{
    batch_insert_to(root, t);
}

void BinarySearchTree::batch_insert_to(struct node *x, RedBlackTree *t)
{
    if (x != NULL)
    {
        batch_insert_to(x->left, t);
        t->insert(x->key);
        batch_insert_to(x->right, t);
    }
}

/* RedBlackTree */

void RedBlackTree::left_rotate(struct node *x)
{
    struct node *y = x->right; // set y
    x->right = y->left;        // turn y's left subtree into x's right subtree
    if (y->left != nil)
        y->left->p = x; // link x's parent to y
    y->p = x->p;
    if (x->p == nil)
        root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x; // put x on y's left
    x->p = y;
}

void RedBlackTree::right_rotate(struct node *y)
{
    struct node *x = y->left;

    y->left = x->right;
    if (x->right != nil)
        x->right->p = y;
    x->p = y->p;

    if (y->p == nil)
        root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    x->right = y;
    y->p = x;
}

struct RedBlackTree::node *RedBlackTree::search(int k)
{
    struct node *x = root;
    while (x != nil && k != x->key)
    {
        comp++;
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

int RedBlackTree::batch_search(vector<int> *k)
{
    comp = 0;
    for (vector<int>::iterator it = k->begin(); it != k->end(); ++it)
        search(*it);
    return comp;
}

void RedBlackTree::insert(int k)
{
    struct node *z = new node(k, NULL, NULL, NULL);
    struct node *y = nil;
    struct node *x = root;

    while (x != nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;

    if (y == nil)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = nil;
    z->right = nil;
    z->color = RED;
    insert_fixup(z);
}

void RedBlackTree::insert_fixup(struct node *z)
{
    struct node *y;

    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;  // case 1
                y->color = BLACK;     // case 1
                z->p->p->color = RED; // case 1
                z = z->p->p;          // case 1
            }
            else if (z == z->p->right)
            {
                z = z->p;       // case 2
                left_rotate(z); // case 2
            }
            z->p->color = BLACK;   // case 3
            z->p->p->color = RED;  // case 3
            right_rotate(z->p->p); // case 3
        }
        else
        {
            y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->left)
            {
                z = z->p;
                right_rotate(z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            left_rotate(z->p->p);
        }
    }

    root->color == BLACK;
}

vector<int> *create_random_data(int n)
{
    vector<int> *random_data = new vector<int>;

    // C++ style random number generator
    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, n);

    for (int i = 0; i < n; ++i)
        random_data->push_back(dist(gen));

    return random_data;
}