#include <iostream>
#include <random>

// To track the sum of weight.
int weight_sum = 0;

void insertion_sort(int arr[], int n)
{
    int i, j, key;

    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        weight_sum += arr[i];
        j = i;

        while (arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            weight_sum += arr[j - 1];
            j--;
        }

        arr[j] = key;
        weight_sum += key;
    }
}

inline void swap(int arr[], int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;

    if (a < b)
    {
        weight_sum += 2 * a + b;
    }
    else
    {
        weight_sum += a + 2 * b;
    }
}

int partition(int arr[], int low, int high)
{
    int i, j, pivot;

    if (high > low)
    {
        pivot = arr[low];
        i = low;
        j = high + 1;

        while (1)
        {
            while (arr[++i] < pivot)
                ;

            while (arr[--j] > pivot)
                ;

            if (i >= j)
            {
                break;
            }

            swap(arr, i, j);
        }

        swap(arr, low, j);
    }

    return j;
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
            p = left;
        }

        if (right < last && arr[p] < arr[right])
        {
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

void quicksort(int arr[], int low, int high)
{
    int j;

    if (high > low)
    {
        j = partition(arr, low, high);
        quicksort(arr, low, j - 1);
        quicksort(arr, j + 1, high);
    }
}

int main()
{
    const int N = 1000;
    int arr1[N], arr2[N], arr3[N];

    // C++ style random number generator
    std::random_device rd;                         // non-deterministic generator
    std::mt19937 gen(rd());                        // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, 1000); // distribute results between 1 and 6 inclusive.

    for (int i = 0; i < N; i++)
    {
        arr1[i] = arr2[i] = arr3[i] = dist(gen);
    }

    weight_sum = 0;
    insertion_sort(arr1, N);

    // Sorting results
    for (int i = 0; i < N; i++)
    {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Insertion sort" << std::endl;
    std::cout << "The sum of the moved weight is " << weight_sum << std::endl;

    weight_sum = 0;
    quicksort(arr2, 0, N - 1);

    // Sorting results
    for (int i = 0; i < N; i++)
    {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Quicksort" << std::endl;
    std::cout << "The sum of the moved weight is " << weight_sum << std::endl;

    weight_sum = 0;
    heap_sort(arr3, N);

    // Sorting results
    for (int i = 0; i < N; i++)
    {
        std::cout << arr3[i] << " ";
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Heap sort" << std::endl;
    std::cout << "The sum of the moved weight is " << weight_sum << std::endl;
}