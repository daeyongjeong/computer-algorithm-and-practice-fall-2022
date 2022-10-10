#include <iostream>

const int N = 10000;

// Print prime numbers less than N, max prime number less than N, and number of
// multiplications
int main()
{
    int i, j;
    bool prime_list[N + 1];
    int max_prime = 0;
    int count_mul = 0;

    for (prime_list[1] = false, i = 2; i <= N; i++)
        prime_list[i] = true;

    for (i = 2; i * i <= N; i++)
    {
        if (prime_list[i])
        {
            for (j = i; j <= N / i; j++)
            {
                prime_list[i * j] = false;
                count_mul++;
            }
        }
    }

    for (i = 1; i <= N; i++)
        if (prime_list[i])
        {
            std::cout << i << ' ';
            max_prime = i;
        }
    std::cout << '\\n';
    
    std::cout << "Max prime number: " << max_prime << '\\n';
    std::cout << "Number of multiplication: " << count_mul << '\\n';
}