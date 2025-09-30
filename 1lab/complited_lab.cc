#include <iostream>
#include <locale.h>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string integer_part(int num, int base) {
    if (num == 0) return "0";

    string result = "";
    string alfav = "0123456789ABCDEF"; 

    while (num > 0) {
        result += alfav[num % base]; 
        num /= base; 
    }

    reverse(result.begin(), result.end()); 
    return result;
}

string fractional_part(double fractional, int base) {
    if (fractional == 0) return "0";

    string result = "";
    string alfav = "0123456789ABCDEF";

    for (int i = 0; i < 10 && fractional > 0; i++) {
        fractional *= base; 
        int digit = (int)fractional; //берем целую часть - это очередная цифра
        result += alfav[digit]; 
        fractional -= digit; 
    }

    return result;
}

double to_ten(string num, int base) {
    size_t tochk = num.find('.'); 
    if (tochk == string::npos) {  //если точка не найдена, устанавливаем позицию в конец строки
        tochk = num.length(); 
    }
    double result = 0.0; 
    string alfav = "0123456789ABCDEF";
     //обрабатываем целую часть числа
    for (int i = 0; i < tochk; i++) {
        int digit = alfav.find(toupper(num[i])); //находим значение цифры (A=10, B=11 и тд)
        int power = tochk - i - 1; 
        result += digit * pow(base, power); 
    }
    //обрабатываем дробную часть числа
    for (int i = tochk + 1; i < num.length(); i++) {
        int digit = alfav.find(toupper(num[i]));
        int power = tochk - i; 
        result += digit * pow(base, power); //отрицательная степень: -1, -2, -3...
    }

    return result;
}
void arifm_operation() {
    string num1, num2;
    int base;
    char operation;

    cout << "Enter the first number in base-r system: ";
    cin >> num1;
    cout << "Enter the second number in base-r system: ";
    cin >> num2;
    cout << "Enter the base of the numeral system (2-16): ";
    cin >> base;
    cout << "Enter the operation (+, - or *): "; 
    cin >> operation;

    if (base < 2 || base > 16) {
        cout << "Base must be between 2 and 16" << endl;
        return;
    }

    double num1_ten = to_ten(num1, base);
    double num2_ten = to_ten(num2, base);


    double result_dec;
    switch (operation) {
    case '+':
        result_dec = num1_ten + num2_ten;
        break;
    case '-': 
        result_dec = num1_ten - num2_ten;
        break;
    case '*':
        result_dec = num1_ten * num2_ten;
        break;
    default:
        cout << "Invalid operation" << endl;
        return;
    }


    int integerPart = (int)result_dec;
    double fractionalPart = result_dec - integerPart;

    string integerResult = integer_part(integerPart, base);
    string fractionalResult = fractional_part(fractionalPart, base);

    cout << "Result: " << integerResult;
    if (fractionalResult != "0") {
        cout << "." << fractionalResult;
    }
    cout << endl;


}

int main() {
    setlocale(LC_ALL, "Russian");
    int choise;
    while (true) {
        cout << "Select task" << endl << endl;
        cout << "1. Convert number from decimal to base-r system" << endl;
        cout << "2. Convert number from base-r to decimal system" << endl;
        cout << "3. Addition, subtraction and multiplication of two numbers in base-r system" << endl;  
        cout << "4. Exit program" << endl;
        cout << "Enter task number without dot: ";
        cin >> choise;

        switch (choise) {
        case 1: {
            int base;
            double number;
            cout << "Enter real number: ";
            cin >> number;

            cout << "Enter the base of the target numeral system (2-16): ";
            cin >> base;

            if (base < 2 || base > 16) {
                cout << "Error: base must be between 2 and 16" << endl;
                break;
            }

            int integerPart = (int)number;
            double fractionalPart = number - integerPart;


            string integerResult = integer_part(integerPart, base);
            string fractionalResult = fractional_part(fractionalPart, base);

            cout << "Result: " << integerResult;
            if (fractionalResult != "0") {
                cout << "." << fractionalResult;
            }
            cout << endl;
            break;
        }
        case 2: {
            string number_r;
            int base;

            cout << "Enter number in base-r system: ";
            cin >> number_r;
            cout << "Enter its base (2-16): ";
            cin >> base;

            double result_10 = to_ten(number_r, base);
            cout << "Result in decimal system: " << result_10 << endl;
            break;
        }
        case 3: {
            arifm_operation();
            break;
        }
        case 4: {
            cout << "Program completed" << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice" << endl;
            break;
        }
        }
        cout << endl;
    }

    return 0;
}