# Exercise 1

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

## 주어진 프로그램 분석

주어진 프로그램은 전체적으로 보면 입력 받은 두 수의 차를 출력하는 프로그램이다. 숫자는 클래스의 멤버 변수로 저장되는데, 클래스 생성자를 통해 새 인스턴스가 만들어질 때 그 숫자를 사용자로부터 입력받도록 되어 있다.

## 오류 수정

* fatal error: 'iostream.h' file not found:
표준 헤더 파일이 아닌 iostream.h 대신 컴파일러가 사용하는 표준 헤더인 iostream을 사용해 해결한다.
* error: use of undeclared identifier 'cout'; did you mean 'std::cout'?: iostream 내의 함수들은 namespace std 안에 정의되어 있기 때문에, std::cout 형태로 사용해야 한다. 또는 using 구문을 사용해 namespace std 또는 std::cout을 사용하겠다는 것을 명시해 컴파일러에게 식별자 cout이 정의된 위치를 찾을 수 있게 해야한다. 여기서는 std::cout 형태로 사용해 해결한다.
* error: use of undeclared identifier 'cin'; did you mean 'std::cin'?: 위 에러와 동일하게 std::cin 형태로 사용해 해결한다.

## 프로그램 실행 결과

``` bash
Enter number 7
The value is 7
Enter number 3
Now the value is 4
```

## 시간, 공간 복잡도 분석

프로그램에서 사용되는 알고리즘, 모든 연산이 입력 크기에 구애받지 않기 때문에 시간 복잡도와 공간 복잡도는 O(1)이다.
