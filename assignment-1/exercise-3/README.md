# Exercise 3

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

## 주어진 프로그램 분석

주어진 프로그램은 N개의 노드로 이루어진 원형 연결 리스트에서, 매 M번째 뒤의 노드를 제거할 때 제거되는 순서를 나타내는 프로그램이다.

## 오류 수정

* error: C++ requires a type specifier for all declarations: 함수 main()에 형식 지정자가 없기 때문에 오류가 나타난다. int main()의 형태로 고쳐서 해결한다.
* error: use of undeclared identifier 'cin': 식별자 cin이 정의되어 있지 않다는 오류를 해결하기 위해 헤더 파일 iostream을 포함해야 한다.
* error: use of undeclared identifier 'cout': 위 에러와 동일하게 헤더 파일 iostream을 포함해야 한다.
* error: use of undeclared identifier 'cin'; did you mean 'std::cin'?: iostream 내의 함수들은 namespace std 안에 정의되어 있기 때문에, std::cin 형태로 사용해야 한다. 또는 using 구문을 사용해 namespace std 또는 std::cin을 사용하겠다는 것을 명시해 컴파일러에게 식별자 cin이 정의된 위치를 찾을 수 있게 해야한다. 여기서는 std::cin 형태로 사용해 해결한다.
* error: use of undeclared identifier 'cout'; did you mean 'std::cout'?: 위 에러와 동일하게 std::cout 형태로 사용해 해결한다.

## 프로그램 실행 결과 1

``` bash
8
3
3 6 1 5 2 8 4 7
```

## 문제 해결

count_while 변수를 추가해 while 문이 실행된 횟수를 추적하도록 한다.

## 프로그램 실행 결과 2

``` bash
8
3
3 6 1 5 2 8 4 7
The number of while statement executed: 7
```

## 시간, 공간 복잡도 분석

시간 복잡도는 N과 M이 같은 경우가 최악의 경우이고, 이때 O(n^2)이다.
공간 복잡도는 N개 만큼의 노드가 생기기 때문에 O(N)이다.
