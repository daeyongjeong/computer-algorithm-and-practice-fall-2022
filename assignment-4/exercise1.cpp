#include <iostream>
#include <random>

// To track the number of comparisons and the number of substitutions.
int comparisons = 0;

class PQ
{
private:
    int *arr;
    int n;

    inline void swap(int arr[], int a, int b)
    {
        int tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
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

public:
    PQ(int max)
    {
        arr = new int[max];
        n = max;

        // C++ style random number generator
        std::random_device rd;                      // non-deterministic generator
        std::mt19937 gen(rd());                     // to seed mersenne twister.
        std::uniform_int_distribution<> dist(0, n); // distribute results between 1 and 6 inclusive.

        for (int i = 0; i < n; i++)
        {
            arr[i] = dist(gen);
        }
    }

    ~PQ()
    {
        delete arr;
    }

    void heap_sort()
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
};

int main()
{
    const int N = 10000;
    PQ *test = new PQ(N);

    // average case
    test->heap_sort();
    std::cout << comparisons << " comparisons" << std::endl;
}