#include "Calculator.h"

using namespace std;

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

double Calculator::addition(double x, double y)
{
    return x + y;
}

double Calculator::division(double x, double y)
{
    return x / y;
}

double Calculator::exponent(double x, double y)
{
    return pow(x, y);
}

double Calculator::subtraction(double x, double y)
{
    return x - y;
}

double Calculator::multiplication(double x, double y)
{
    return x * y;
}

double Calculator::root(double x)
{
    return sqrt(x);
}

double Calculator::square(double x)
{
    return pow(x, 2);
}

int main(int argc, char *argv[])
{
    Calculator calc = Calculator();
    bool isRun = true;

    while (isRun)
    {
        double num1;
        int opNum;
        cout << endl
             << "Enter a number: ";
        cin >> num1;

        // catch bad inputs (non numbers) to avoid infinite loop
        if (cin.fail())
        {
            cout << "ERROR -- You did not enter a number" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            cout << endl << "List of operations: " << endl
                 << "1. add " << "2. subtract " << "3. multiply " << "4. divide" << endl
                 << "5. square" << " 6. power" << " 7. root " << "8. exit" << endl;

            cout << endl << "Choose an operation (enter the number): ";
            cin >> opNum;
            // catch bad inputs (non numbers) to avoid infinite loop
            if (cin.fail())
            {
                cout << "ERROR -- You did not enter an integer" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                bool validOp = false;
                for (int i = 1; i < 9; i++)
                {
                    if (opNum == i)
                    {
                        validOp = true;
                    }
                }
                if (validOp == true)
                {
                    if (opNum == 5)
                    {
                        // square
                        cout << "Square of " << num1 << " is: " << calc.square(num1) << endl;
                    }
                    else if (opNum == 7)
                    {
                        // root
                        cout << "Root of " << num1 << " is: " << calc.root(num1) << endl;
                    }
                    else if (opNum == 8)
                    {
                        // exit
                        exit(1);
                    }
                    else
                    {
                        int num2;
                        cout << endl
                             << "Enter a second number: ";
                        cin >> num2;

                        // catch bad inputs (non numbers) to avoid infinite loop
                        if (cin.fail())
                        {
                            cout << "ERROR -- You did not enter a number" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        else
                        {
                            switch (opNum)
                            {
                            case 1:
                                cout << "Sum of " << num1 << " and " << num2 << " is: " << calc.addition(num1, num2) << endl;
                                break;
                            case 2:
                                cout << "Difference of " << num1 << " and " << num2 << " is: " << calc.subtraction(num1, num2) << endl;
                                break;
                            case 3:
                                cout << "Product of " << num1 << " and " << num2 << " is: " << calc.multiplication(num1, num2) << endl;
                                break;
                            case 4:
                                cout << "Quotient of " << num1 << " and " << num2 << " is: " << calc.division(num1, num2) << endl;
                                break;
                            case 6:
                                cout << "Power of " << num1 << " and " << num2 << " is: " << calc.exponent(num1, num2) << endl;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}