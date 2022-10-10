# 1주차 실습

## [Exercise 1](exercise-1)

다음 프로그램을 실행할 때 필요한 값을 입력(_num)하여 실습하시오.

``` C++
#include <iostream.h>
class InputNum
{
public:
    InputNum()
    {
        cout << "Enter number ";
        cin >> _num;
    }

    int GetValue() const { return _num; }

    void SubtractInput()
    {
        InputNum aNum; // get a number from user
        _num = _num - aNum.GetValue();
    }

private:
    int _num;
};

int main()
{
    InputNum num;
    cout << "The value is " << num.GetValue() << "\\n";
    num.SubtractInput();
    cout << "Now the value is " << num.GetValue() << "\\n";
}
```

## [Exercise 2](exercise-2)

다음 프로그램을 수행할 때 주어진 N에 대해서 N보다 작은 소수(Prime)들을 출력하시오. 또한 N=10000 일 때 N보다 작은 최대 소수를 출력하고, 이때 실행된 곱셈 연산 횟수를 출력하시오.

``` C++
const int N = 500;

main()
{
    int i, j, a[N + 1];
    for (a[1] = 0, i = 2; i <= N; i++)
        a[i] = 1;
    for (i = 2; i <= N / 2; i++)
        for (j = 2; j <= N / i; j++)
            a[i * j] = 0;
    for (i = 1; i <= N; i++)
        if (a[i])
            cout << i << ' ';
    cout << '\\n';
}
```

## [Exercise 3](exercise-3)

다음 프로그램을 실행하여 M, N의 값을 입력하고, 주어진 M, N의 값에 대해서 알고리즘 수행 과정에서 while loop가 실행된 횟수를 count해서 출력하시오.

``` C++
struct node
{
    int key;
    struct node *next;
};

main()
{
    int i, N, M;
    struct node *t,*x;
    cin >> N >> M;
    t = new node;
    t->key = 1;
    x = t;
    for (i = 2; i <= N; i++)
    {
        t->next = new node;
        t = t->next;
        t->key = i;
    }
    t->next = x;
    while (t != t->next)
    {
        for (i = 1; i < M; i++)
            t = t->next;
        cout << t->next->key << ' ';
        x = t->next;
        t->next = x->next;
        delete x;
    }
    cout << t->key << '\\n';
}
```
