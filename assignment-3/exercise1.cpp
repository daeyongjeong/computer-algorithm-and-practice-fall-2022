// Fix C-style code to the C++ style.

#include <random>
#include <iostream>

using namespace std;

void insertion_sort(int a[], int n)
{
    int i, j, key;
    for (i = 2; i <= n; i++)
    {
        key = a[i];
        j = i;

        while (a[j - 1] > key)
        {
            a[j] = a[j - 1];
            j--;
        }

        a[j] = key;
    }
}

int main()
{
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 1000); // distribute results between 1 and 6 inclusive.

    for (int i = 0; i < 5; ++i) {
        cout << dist(gen) << " "; // pass the generator to the distribution.
    }
    cout << endl;

    int n = 1001;
    itemType *a = new itemType[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        printf("%5d;", a[i]);
    }

    printf("\n\n\n\n");
    insertion(a, n);
    for (int i = 0; i < n; i++)
    {
        printf("%5d;", a[i]);
    }
}