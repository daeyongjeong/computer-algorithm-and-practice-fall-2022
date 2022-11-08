#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    random_device rd;                       // non-deterministic generator
    mt19937 gen(rd());                      // to seed mersenne twister.
    uniform_int_distribution<> dist(1, 99); // distribute results between 1 and 6 inclusive.

    // input arrays
    int *a = new int[n];
    int *b = new int[m];

    // output arrays
    int *u = new int[n + m];
    int *x = new int[max(n, m)];

    // iterators
    int i, j, k;

    // make array with random numbers
    for (int i = 0; i < n; i++)
        a[i] = dist(gen);
    for (int i = 0; i < m; i++)
        b[i] = dist(gen);

    // sort (quicksort)
    sort(a, a + n);
    sort(b, b + n);

    // print a
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;

    // print b
    for (int i = 0; i < m; i++)
        cout << b[i] << ' ';
    cout << endl;

    // union
    i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] <= b[j])
        {
            if (k == 0 || u[k - 1] != a[i])
                u[k++] = a[i];
            i++;
        }
        else
        {
            if (k == 0 || u[k - 1] != b[j])
                u[k++] = b[j++];
            j++;
        }
    }
    while (i < n)
    {
        if (k == 0 || u[k - 1] < a[i])
            u[k++] = a[i];
        i++;
    }
    while (j < m)
    {
        if (k == 0 || u[k - 1] < b[j])
            u[k++] = b[j++];
        j++;
    }

    // print union
    for (int i = 0; i < k; i++)
        cout << u[i] << ' ';
    cout << endl;

    // intersection
    i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
            i++;
        else if (a[i] > b[j])
            j++;
        else
        {
            x[k++] = a[i++];
            j++;
        }
    }

    // print intersection
    for (int i = 0; i < k; i++)
        cout << x[i] << ' ';
    cout << endl;
}
