#include <iostream>
#include <string>
using namespace std;

/* Function declarations */
void brute_force_matcher(const char text[100][100], const char pattern[10][10]);
void rabin_karp_matcher(const char text[100][100], const char pattern[10][10], const int radix, const int prime);
void print_comparisons();
void print_spurious_hit(const int col, const int row);
void print_valid_shift(const char text[100][100], const char pattern[10][10], const int col, const int row);
bool test_valid_shift(const char text[100][100], const char pattern[10][10], const int col, const int row);

/* Const definitions */
const int n = 100;
const int m = 10;

/* Data declarations */
int comparison = 0;

/* Main function */
int main()
{
    char text[100][100];
    char pattern[10][10];

    for (int i = 0; i < 100; ++i)
        for (int j = 0; j < 100; ++j)
            text[i][j] = 'A';
    text[99][99] = 'B';

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            pattern[i][j] = 'A';
    pattern[9][9] = 'B';

    rabin_karp_matcher(text, pattern, 32, 33554393);
    brute_force_matcher(text, pattern);
}

/* Function definitions */
bool test_valid_shift(const char text[100][100], const char pattern[10][10], const int col, const int row)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            comparison += 1;
            if (pattern[i][j] != text[col + i][row + j])
                return false;
        }
    }
    return true;
}

void print_valid_shift(const char text[100][100], const char pattern[10][10], const int col, const int row)
{
    cout << "Pattern occurs with col " << col << ", row " << row << endl;
}

void print_spurious_hit(const int col, const int row)
{
    cout << "Pattern hits spurious with col " << col << ", row " << row << endl;
}

void print_comparisons()
{
    cout << "Comparisons " << comparison << endl;
}

void brute_force_matcher(const char text[100][100], const char pattern[10][10])
{
    comparison = 0;

    for (int col = 0; col <= n - m; ++col)
        for (int row = 0; row <= n - m; ++row)
            if (test_valid_shift(text, pattern, col, row))
                print_valid_shift(text, pattern, col, row);
    print_comparisons();
}

// hash only first row in matrix[10][10]
void rabin_karp_matcher(const char text[100][100], const char pattern[10][10], const int radix, const int prime)
{
    int h = 1;
    long p = 0;
    long t = 0;
    comparison = 0;

    // initialize h to value of high-order digit position
    for (int i = 0; i < m - 1; ++i)
        h = (h * radix) % prime;

    // preprocessing
    for (int i = 0; i < m; ++i)
    {
        p = (p * radix + pattern[0][i]) % prime;
        t = (t * radix + text[0][i]) % prime;
    }

    // matching
    for (int col = 0; col <= n - m; ++col)
    {
        for (int row = 0; row <= n - m; ++row)
        {
            if (p == t) // hit
            {
                cout << "col: " << col << ", row: " << row << ", p: " << p << ", t: " << t << endl;
                if (test_valid_shift(text, pattern, col, row))
                    print_valid_shift(text, pattern, col, row);
                else
                    print_spurious_hit(col, row);
            }

            if (row < n - m) // compute value for next window
            {
                t = ((t - text[col][row] * h) * radix + text[col][row + m]) % prime;
                t = (t + prime) % prime;
            }
        }

        if (col < n - m) // compute value for next window
        {
            t = 0;
            for (int i = 0; i < m; ++i)
                t = (t * radix + text[col + 1][i]) % prime;
        }
    }
    print_comparisons();
}
