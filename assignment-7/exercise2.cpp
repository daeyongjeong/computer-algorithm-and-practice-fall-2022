#include <iostream>
#include <random>

using namespace std;

class HashTable
{
private:
    const int NIL = -1;

    int t[3001];  // table
    int m = 3001; // table length
    int comp = 0; // for track key comparisons

    int h(int k, int i)
    {
        return (k + i) % m;
    }

public:
    HashTable()
    {
        fill_n(t, 3001, -1);
    }

    int insert(int k)
    {
        for (int i = 0; i != m; ++i)
        {
            int j = h(k, i);
            if (t[j] == NIL)
            {
                t[j] = k;
                return j;
            }
        }
        return -1; // hash table overflow
    }

    int search(int k)
    {
        int i = 0;
        int j;
        do
        {
            j = h(k, i);
            comp++;
            if (t[j] == k)
                return j;
            i = i + 1;
        } while (t[j] != NIL && i != m);
        return NIL;
    }

    void batch_insert(vector<int> *k)
    {
        for (vector<int>::iterator it = k->begin(); it != k->end(); ++it)
        {
            insert(*it);
        }
    }

    int batch_search(vector<int> *k)
    {
        comp = 0;
        for (vector<int>::iterator it = k->begin(); it != k->end(); ++it)
            search(*it);
        return comp;
    }
};

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

int main()
{
    const int N = 1000;
    vector<int> *random_data = create_random_data(N);

    HashTable ht;
    int comp = 0;

    ht.batch_insert(random_data);

    cout << "Hash table search" << endl;
    comp = ht.batch_search(random_data);
    cout << "Total comparisons\t" << comp << endl;
    cout << "Average comparisons\t" << comp / N << endl;
}