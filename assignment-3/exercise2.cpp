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
            {
                comparisons++;
            }

            while (arr[--j] > pivot)
            {
                comparisons++;
            }

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
    int arr[N];

    // C++ style random number generator
    std::random_device rd;                         // non-deterministic generator
    std::mt19937 gen(rd());                        // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, 1000); // distribute results between 1 and 6 inclusive.

    for (int i = 0; i < N; i++)
    {
        arr[i] = dist(gen);
    }

    quicksort(arr, 0, N - 1);

    // Sorting results
    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Quicksort" << std::endl;
    std::cout << comparisons << " comparisons" << std::endl;
    std::cout << substitutions << " substitutions" << std::endl;
}