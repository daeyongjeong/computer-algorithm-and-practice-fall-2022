#include <iostream>
#include <random>

// To track the number of comparisons and the number of substitutions.
int comparisons = 0;
int substitutions = 0;

inline void swap(int arr[], int a, int b)
{
    int tmp = arr[a];

    arr[a] = arr[b];
    substitutions++;

    arr[b] = tmp;
    substitutions++;
}

void heapify(int arr[], int root, int last)
{
    int left, right, p;
    while (root < last)
    {
        left = root * 2 + 1;
        right = root * 2 + 2;

        if (left >= last && right >= last)
        {
            break;
        }

        p = root;

        if (left < last && arr[p] < arr[left])
        {
            comparisons++;
            p = left;
        }

        if (right < last && arr[p] < arr[right])
        {
            comparisons++;
            p = right;
        }

        if (p == root)
        {
            break;
        }

        swap(arr, root, p);
        root = p;
    }
}

void heap_sort(int arr[], int n)
{
    for (int i = n / 2; i > 0; i--)
    {
        heapify(arr, i - 1, n - 1);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr, 0, i);
        heapify(arr, 0, i - 1);
    }
}

int main()
{
    const int N = 1000;
    int arr[N];

    // C++ style random number generator
    std::random_device rd;                         // non-deterministic generator
    std::mt19937 gen(rd());                        // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, 1000); // distribute results between 1 and 6 inclusive.

    for (int i = 0; i < N; i++)
    {
        arr[i] = dist(gen);
    }

    heap_sort(arr, N);

    // Sorting results
    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Heap sort" << std::endl;
    std::cout << comparisons << " comparisons" << std::endl;
    std::cout << substitutions << " substitutions" << std::endl;
}
