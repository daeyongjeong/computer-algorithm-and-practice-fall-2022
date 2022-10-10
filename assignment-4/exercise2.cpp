#include <iostream>
#include <random>

// To track the number of comparisons.
int comparisons = 0;

inline void swap(int arr[], int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
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

void select(int arr[], int low, int high, int k)
{
    int j;
    if (high > low)
    {
        j = partition(arr, low, high);

        if (j > low + k - 1)
        {
            select(arr, low, j - 1, k);
        }

        if (j < low + k - 1)
        {
            select(arr, j + 1, high, k - j + low - 1);
        }
    }
}

int main()
{
    const int N = 10000;
    int arr[N];

    // C++ style random number generator
    std::random_device rd;                          // non-deterministic generator
    std::mt19937 gen(rd());                         // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, 10000); // distribute results between 1 and 6 inclusive.

    for (int i = 0; i < N; i++)
    {
        arr[i] = dist(gen);
    }

    select(arr, 0, N - 1, 0);
    std::cout << "Mininum: " << arr[0] << std::endl;

    select(arr, 0, N - 1, N - 1);
    std::cout << "Maximum: " << arr[N - 1] << std::endl;

    select(arr, 0, N - 1, N / 2);
    if (N % 2)
    {
        std::cout << "Median: " << arr[N / 2] << std::endl;
    }
    else
    {
        std::cout << "Median: " << (arr[N / 2] + arr[N / 2 - 1]) / 2 << std::endl;
    }

    std::cout << comparisons << " comparisons" << std::endl;
}