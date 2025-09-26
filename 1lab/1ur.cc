#include <iostream>
#include <locale.h>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Функция для перевода положительного числа в двоичную систему
string positive_to_binary(int num) {
    if (num == 0) return "0";
    
    string result = "";
    while (num > 0) {
        result += (num % 2 == 0) ? '0' : '1';
        num /= 2;
    }
    reverse(result.begin(), result.end());
    return result;
}

// Функция для перевода целой части числа
string integer_part(int num, int base) {
    if (num == 0) return "0";

    // Для двоичной системы с отрицательными числами - дополнительный код
    if (base == 2 && num < 0) {
        // Берем модуль числа и переводим в двоичную
        int positive_num = abs(num);
        string binary = positive_to_binary(positive_num);
        
        // Дополняем нулями до нужной длины (минимум 4 бита)
        int min_bits = max((int)binary.length() + 1, 4);
        while (binary.length() < min_bits) {
            binary = "0" + binary;
        }
        
        // Инвертируем биты (заменяем 0 на 1 и 1 на 0)
        string inverted = "";
        for (char c : binary) {
            inverted += (c == '0') ? '1' : '0';
        }
        
        // Добавляем 1
        string result = inverted;
        bool carry = true;
        for (int i = result.length() - 1; i >= 0 && carry; i--) {
            if (result[i] == '0') {
                result[i] = '1';
                carry = false;
            } else {
                result[i] = '0';
            }
        }
        
        // Если был перенос, добавляем 1 в начало
        if (carry) {
            result = "1" + result;
        }
        
        return result;
    }

    // Для остальных систем и положительных двоичных
    bool negative = false;
    if (num < 0) {
        negative = true;
        num = abs(num);
    }

    string result = "";
    string alfav = "0123456789ABCDEF";

    while (num > 0) {
        result += alfav[num % base];
        num /= base;
    }

    reverse(result.begin(), result.end());
    
    if (negative && base != 2) {
        result = "-" + result;
    }
    
    return result;
}

// Функция для перевода дробной части числа
string fractional_part(double fractional, int base) {
    if (fractional == 0) return "0";

    fractional = abs(fractional);
    
    string result = "";
    string alfav = "0123456789ABCDEF";

    for (int i = 0; i < 10 && fractional > 0; i++) {
        fractional *= base;
        int digit = (int)fractional;
        result += alfav[digit];
        fractional -= digit;
    }

    return result;
}

// Перевод в 10-ную систему счисления 
double to_ten(string num, int base) {
    // Для двоичной системы проверяем, является ли число дополнительным кодом
    if (base == 2 && num.find('.') == string::npos && num.find('-') == string::npos) {
        // Если старший бит = 1, то это может быть дополнительный код
        if (!num.empty() && num[0] == '1') {
            // Проверяем, действительно ли это дополнительный код
            bool is_twos_complement = true;
            for (char c : num) {
                if (c != '0' && c != '1') {
                    is_twos_complement = false;
                    break;
                }
            }
            
            if (is_twos_complement) {
                // Преобразуем из дополнительного кода обратно
                string inverted = "";
                for (char c : num) {
                    inverted += (c == '0') ? '1' : '0';
                }
                
                // Вычитаем 1 (добавляем -1 в двоичной)
                string temp = inverted;
                bool borrow = true;
                for (int i = temp.length() - 1; i >= 0 && borrow; i--) {
                    if (temp[i] == '1') {
                        temp[i] = '0';
                        borrow = false;
                    } else {
                        temp[i] = '1';
                    }
                }
                
                // Переводим в десятичную и делаем отрицательным
                int value = 0;
                for (int i = 0; i < temp.length(); i++) {
                    if (temp[i] == '1') {
                        value += (1 << (temp.length() - 1 - i));
                    }
                }
                
                return -value;
            }
        }
    }

    bool negative = false;
    if (num[0] == '-') {
        negative = true;
        num = num.substr(1);
    }
    
    size_t tochk = num.find('.');
    if (tochk == string::npos) {
        tochk = num.length();
    }
    
    double result = 0.0;
    string alfav = "0123456789ABCDEF";

    // Целая часть
    for (int i = 0; i < tochk; i++) {
        int digit = alfav.find(toupper(num[i]));
        if (digit == string::npos || digit >= base) {
            cout << "Error: Invalid digit '" << num[i] << "' for base " << base << endl;
            return 0;
        }
        int power = tochk - i - 1;
        result += digit * pow(base, power);
    }

    // Дробная часть
    for (int i = tochk + 1; i < num.length(); i++) {
        int digit = alfav.find(toupper(num[i]));
        if (digit == string::npos || digit >= base) {
            cout << "Error: Invalid digit '" << num[i] << "' for base " << base << endl;
            return 0;
        }
        int power = tochk - i;
        result += digit * pow(base, power);
    }

    if (negative) {
        result = -result;
    }
    
    return result;
}

// Арифметические операции +|*
void arifm_operation() {
    string num1, num2;
    int base;
    char operation;

    cout << "Enter the 1st number of r system: ";
    cin >> num1;
    cout << "Enter the 2nd number of r system: ";
    cin >> num2;
    cout << "Enter radix (2-16): ";
    cin >> base;
    cout << "Enter operation (+ or *): ";
    cin >> operation;

    if (base < 2 || base > 16) {
        cout << "radix must be from 2 to 16" << endl;
        return;
    }

    double num1_ten = to_ten(num1, base);
    double num2_ten = to_ten(num2, base);

    double result_dec;
    switch (operation) {
    case '+':
        result_dec = num1_ten + num2_ten;
        break;
    case '*':
        result_dec = num1_ten * num2_ten;
        break;
    default:
        cout << "invalid operation" << endl;
        return;
    }

    cout << "1st number in decimal system: " << num1_ten << endl;
    cout << "2nd number in decimal system: " << num2_ten << endl;
    cout << "Result in decimal system: " << result_dec << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "Enter the case" << endl << endl;
        cout << "1. Convert a number from the decimal system to the r-th system" << endl;
        cout << "2. Convert a number from r-ary to decimal" << endl;
        cout << "3. Addition and multiplication of two numbers in the r-ary system" << endl;
        cout << "4. Completion of the program" << endl;
        cout << "Enter the program number without dot: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double number;
            int base;
            cout << "Enter the real number: ";
            cin >> number;

            cout << "Enter the base of the number system you want to convert to (2-16): ";
            cin >> base;

            if (base < 2 || base > 16) {
                cout << "The base must be between 2 and 16" << endl;
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

            cout << "Enter the number in r-based system: ";
            cin >> number_r;
            cout << "Specify its base of the number system (2-16): ";
            cin >> base;

            double result_10 = to_ten(number_r, base);
            cout << "Result in the decimal system: " << result_10 << endl;
            break;
        }
        case 3: {
            arifm_operation();
            break;
        }
        case 4: {
            cout << "End of program" << endl;
            return 0;
        }
        default: {
            cout << "invalid choice" << endl;
            break;
        }
        }
        cout << endl;
    }

    return 0;
}
