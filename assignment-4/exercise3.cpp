#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct WordCount
{
    std::string word;
    int count;
};

bool comp(const WordCount &x, const WordCount &y)
{
    return x.word < y.word;
}

void swap(WordCount &x, WordCount &y)
{
    WordCount tmp = x;
    x = y;
    y = tmp;
}

void make_heap(std::vector<WordCount> &arr, int first, int last)
{
    int left, right, p;

    while (first < last)
    {
        left = first * 2 + 1;
        right = first * 2 + 2;

        if (left >= last && right >= last)
        {
            break;
        }

        p = first;

        if (left < last && comp(arr[p], arr[left]))
        {
            p = left;
        }

        if (right < last && comp(arr[p], arr[right]))
        {
            p = right;
        }

        if (p == first)
        {
            break;
        }

        swap(arr[first], arr[p]);
        first = p;
    }
}

void sort_heap(std::vector<WordCount> &arr)
{
    int size = arr.size();
    for (int i = size / 2; i > 0; i--)
    {
        make_heap(arr, i - 1, size - 1);
    }

    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        make_heap(arr, 0, i - 1);
    }
}

int findword(const std::vector<WordCount> &words,
             const std::string &word)
{
    for (auto w = words.begin(); w != words.end(); w++)
        if (w->word == word)
            return w - words.begin();

    return -1;
}

int main()
{
    const std::string delim = "~!@#$%^&*()_+`-={}[]\\|;:'\"<>,./?";
    const std::string filename = "datafile.txt";
    std::string word;
    std::vector<WordCount> words;
    std::fstream f(filename);

    while (f >> word)
    {
        // Remove special characters
        for (char c : delim)
            word.erase(std::remove(word.begin(), word.end(), c), word.end());

        // Converts word to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        int idx = findword(words, word);
        if (idx != -1)
        {
            words[idx].count++;
        }
        else
        {
            WordCount tmp = {word, 1};
            words.push_back(tmp);
        }
    }

    sort_heap(words);

    int count = 0;
    for (auto &w : words)
    {
        if (count >= 30)
            break;

        std::cout << count + 1 << ": (" << w.word << ", " << w.count << ")" << std::endl;
        count++;
    }
}