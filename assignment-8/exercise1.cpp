#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* Function declarations */
void brute_force_matcher(const string text, const string pattern);
void rabin_karp_matcher(const string text, const string pattern, const int radix, const int prime);
void kmp_matcher(const string text, const string pattern);
vector<int> compute_prefix_function(const string pattern);
void print_valid_shift(const string text, const string pattern, const int shift);
bool test_valid_shift(const string text, const string pattern, const int shift);

/* Data declarations */
int comparison = 0;

/* Main function */
int main()
{
    const string text = "A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN STING";
    const string pattern = "STING";
    brute_force_matcher(text, pattern);
    rabin_karp_matcher(text, pattern, 32, 33554393);
    kmp_matcher(text, pattern);
    return 0;
}

/* Function definitions */
bool test_valid_shift(const string text, const string pattern, const int shift)
{
    const int m = pattern.length();

    for (int i = 0; i < m; ++i)
    {
        comparison += 1;
        if (pattern[i] != text[shift + i])
            return false;
    }
    return true;
}

void print_valid_shift(const string text, const string pattern, const int shift)
{
    cout << "Pattern occurs with shift " << shift << endl;
    cout << text << endl;
    for (int i = 0; i < shift; ++i)
    {
        cout << ' ';
    }
    cout << pattern << endl
         << endl;
}

void print_spurious_hit(const int shift)
{
    cout << "Pattern hits spurious with shift " << shift << endl;
}

void print_comparisons()
{
    cout << "Comparisons " << comparison << endl;
}

void brute_force_matcher(const string text, const string pattern)
{
    const int n = text.length();
    const int m = pattern.length();
    comparison = 0;

    for (int shift = 0; shift <= n - m; ++shift)
        if (test_valid_shift(text, pattern, shift))
            print_valid_shift(text, pattern, shift);
    print_comparisons();
}

void rabin_karp_matcher(const string text, const string pattern, const int radix, const int prime)
{
    const int n = text.length();
    const int m = pattern.length();
    int h = 1;
    int p = 0;
    int t = 0;
    comparison = 0;

    // initialize h to value of high-order digit position
    for (int i = 0; i < m - 1; ++i)
        h = (h * radix) % prime;

    // preprocessing
    for (int i = 0; i < m; ++i)
    {
        p = (p * radix + pattern[i]) % prime;
        t = (t * radix + text[i]) % prime;
    }

    // matching
    for (int shift = 0; shift <= n - m; ++shift)
    {
        if (p == t) // hit
        {
            if (test_valid_shift(text, pattern, shift))
                print_valid_shift(text, pattern, shift);
            else
                print_spurious_hit(shift);
        }

        if (shift < n - m) // compute value for next window
        {
            t = ((t - text[shift] * h) * radix + text[shift + m]) % prime;
            t = (t + prime) % prime;
        }
    }
    print_comparisons();
}

vector<int> compute_prefix_function(const string pattern)
{
    const int m = pattern.length();
    int k = 0;
    vector<int> pi; // pi[q] is length of longest prefix of pattern that is proper suffix of pattern[0..q]

    // initialize pi with 0
    for (int i = 0; i < m; ++i)
        pi.push_back(0);

    // compute prefix function
    for (int q = 1; q < m; ++q)
    {
        while (k > 0 && pattern[k] != pattern[q])
            k = pi[k];
        if (pattern[k] == pattern[q])
            k = k + 1;
        pi[q] = k;
    }
    return pi;
}

void kmp_matcher(const string text, const string pattern)
{
    const int n = text.length();
    const int m = pattern.length();
    const vector<int> pi = compute_prefix_function(pattern);
    int q = 0; // number of characters matched
    comparison = 0;

    for (int i = 0; i < n; ++i)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            comparison += 1;
            q = pi[q];
        }

        comparison += 1;
        if (pattern[q] == text[i])
            q = q + 1;

        if (q == m)
        {
            print_valid_shift(text, pattern, i - m + 1);
            q = pi[q];
        }
    }
    print_comparisons();
}
