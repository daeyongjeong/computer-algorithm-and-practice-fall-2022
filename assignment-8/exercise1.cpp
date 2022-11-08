#include <string>
#include <iostream>
#include <vector>
using namespace std;

void naive_string_matcher(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    for (int s = 0; s <= n - m; ++s)
        if (pattern == text.substr(s, m))
            cout << "Pattern occurs with shift " << s << endl;
}

void rabin_karp_matcher(string text, string pattern, int radix, int prime)
{
    int n = text.length();
    int m = pattern.length();
    int h = 1;
    int p = 0;
    int t = 0;
    for (int i = 0; i < m - 1; ++i)
        h = (h * radix) % prime;
    for (int i = 0; i < m; ++i)
    {
        p = (p * radix + pattern[i]) % prime;
        t = (t * radix + text[i]) % prime;
    }
    for (int s = 0; s <= n - m; ++s)
    {
        if (p == t)
            if (pattern == text.substr(s, m))
                cout << "Pattern occurs with shift " << s << endl;
        if (s < n - m)
        {
            t = ((t - text[s] * h) * radix + text[s + m]) % prime;
            t = (t + prime) % prime;
        }
    }
}

vector<int> compute_prefix_function(string pattern)
{
    int m = pattern.length();
    vector<int> pi;
    for (int i = 0; i < m; ++i)
        pi.push_back(0);
    int k = 0;
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

void kmp_matcher(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    vector<int> pi = compute_prefix_function(pattern);
    int q = 0;
    for (int i = 0; i < n; ++i)
    {
        while (q > 0 && pattern[q] != text[i])
            q = pi[q];
        if (pattern[q] == text[i])
            q = q + 1;
        if (q == m)
        {
            cout << "Pattern occurs with shift " << i - m + 1 << endl;
            q = pi[q];
        }
    }
}

int main()
{
    const string text = "A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN STING";
    const string pattern = "STING";

    naive_string_matcher(text, pattern);
    rabin_karp_matcher(text, pattern, 32, 33554393);
    kmp_matcher(text, pattern);
}
