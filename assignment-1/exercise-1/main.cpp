#include <iostream>

class InputNum
{
public:
    // Enter a new number
    InputNum()
    {
        std::cout << "Enter number ";
        std::cin >> _num;
    }

    // Return number value
    int getValue() const
    {
        return _num;
    }

    // Enter a new number and subtract from _num
    void subtractInput()
    {
        InputNum aNum; // get a number from user
        _num = _num - aNum.getValue();
    }

private:
    int _num;
};

int main()
{
    InputNum num;

    std::cout << "The value is " << num.getValue() << "\\n";
    num.subtractInput();
    std::cout << "Now the value is " << num.getValue() << "\\n";
}