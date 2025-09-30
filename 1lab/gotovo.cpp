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

    cout << "Введите первое число в r системе счисления: ";
    cin >> num1;
    cout << "Введите второе число в r системе счисления: ";
    cin >> num2;
    cout << "Введите основание системы счисления (2-16): ";
    cin >> base;
    cout << "Введите операцию (+, - или *): "; 
    cin >> operation;

    if (base < 2 || base > 16) {
        cout << "основание должно быть от 2 до 16" << endl;
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
        cout << "неверная операция" << endl;
        return;
    }


    int integerPart = (int)result_dec;
    double fractionalPart = result_dec - integerPart;

    string integerResult = integer_part(integerPart, base);
    string fractionalResult = fractional_part(fractionalPart, base);

    cout << "Результат: " << integerResult;
    if (fractionalResult != "0") {
        cout << "." << fractionalResult;
    }
    cout << endl;


}

int main() {
    setlocale(LC_ALL, "Russian");
    int choise;
    while (true) {
        cout << "Выберите задачу" << endl << endl;
        cout << "1. Перевести число из 10-ичной системы в r-ичную" << endl;
        cout << "2. Перевести число из r-ичной в десятичную" << endl;
        cout << "3. Сложение, вычитание и умножение двух чисел в r-ичной системе" << endl;  
        cout << "4. Завершение программы" << endl;
        cout << "Введите номер задачи без точки: ";
        cin >> choise;

        switch (choise) {
        case 1: {
            int base;
            double number;
            cout << "Введите вещественное число: ";
            cin >> number;

            cout << "Введите основание системы счисления, в которую хотите перевести (2-16): ";
            cin >> base;

            if (base < 2 || base > 16) {
                cout << "Неверно, основание должно быть от 2 до 16" << endl;
                break;
            }

            int integerPart = (int)number;
            double fractionalPart = number - integerPart;


            string integerResult = integer_part(integerPart, base);
            string fractionalResult = fractional_part(fractionalPart, base);

            cout << "Результат: " << integerResult;
            if (fractionalResult != "0") {
                cout << "." << fractionalResult;
            }
            cout << endl;
            break;
        }
        case 2: {
            string number_r;
            int base;

            cout << "Введите число в r-ичной системе: ";
            cin >> number_r;
            cout << "Укажите его основание системы счисления (2-16): ";
            cin >> base;

            double result_10 = to_ten(number_r, base);
            cout << "Результат в 10-ичной системе: " << result_10 << endl;
            break;
        }
        case 3: {
            arifm_operation();
            break;
        }
        case 4: {
            cout << "Программа завершена" << endl;
            return 0;
        }
        default: {
            cout << "Неверный выбор" << endl;
            break;
        }
        }
        cout << endl;
    }

    return 0;
}
