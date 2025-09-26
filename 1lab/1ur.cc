#include <iostream>
#include <locale.h>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

//funcziya dlya perevoda zeloy chasty chisla
string integer_part(int num, int base) {
    if (num == 0) return "0";

    string result = "";
    string alfav = "0123456789ABCDEF"; //alfavit sistem schislenya do 16 vkluchitel`no

    while (num > 0) {
        result += alfav[num % base]; //berem ostatok ot delenya 
        num /= base; //umen`shaem chislo vo stoka raz kakaya sistema schisleniya u nas
    }

    reverse(result.begin(), result.end()); //nado perevernut` chislo dlya zapisi rezultata
    return result;
}

//funcziya dlya perevoda drobnoy chasty chisla
string fractional_part(double fractional, int base) {
    if (fractional == 0) return "0";

    string result = "";
    string alfav = "0123456789ABCDEF";

    for (int i = 0; i < 10 && fractional > 0; i++) {
        fractional *= base; //umnojaem na osnovanie systemi
        int digit = (int)fractional; //berem poluchivshyusya zelyu chast` chisla
        result += alfav[digit]; //zapisyvaem ee v resultat nash
        fractional -= digit; //otnimaem zeluy chast chisla, dal`she vichislyaem
    }

    return result;
}

//perevod v 10 sistemy schisleniya 
double to_ten(string num, int base) {
    size_t tochk = num.find('.'); //oprredelyaem posiziu tochki
    if (tochk == string::npos) {
        tochk = num.length(); //proverka esly tochki net, to govorim chto tochka v konze chisla
    }
    double result = 0.0; 
    string alfav = "0123456789ABCDEF";

    //zdes` schitaem zeluy chast` chisla 
    for (int i = 0; i < tochk; i++) {
        int digit = alfav.find(toupper(num[i])); //nahodim znachenie zifri 
        int power = tochk - i - 1; //nahodim stepen` v kotoruy budem vvodi` osnovanie sistemi: 123(10) = 1*10**2 + 2*10**1 + 3*10**0
        result += digit * pow(base, power); //proizvodim to chto vishe v primere pokazala
    }

    //zdes` schitaem drobnuy chast` chisla 
    for (int i = tochk + 1; i < num.length(); i++) {
        int digit = alfav.find(toupper(num[i]));
        int power = tochk - i; //kogda vicheslyaem drobnuy chast` mi ymnojaem na otrizatel`nuy stepen`: 0.101(2)= 1*2**-1 + 0*2**-2 + 1*2**-3
        result += digit * pow(base, power);
    }

    return result;
}

// +|*  (punkt 4)
void arifm_operation() {
    string num1, num2; //2 chisla vvodim
    int base;
    char operation; //vibor operazii

    cout << "Enter the 1st number of r system: ";
    cin >> num1;
    cout << "Enter the 2nd number of r system: ";
    cin >> num2;
    cout << "Enter radix (2-16): ";
    cin >> base;
    cout << "Enter operation (+ or *): ";
    cin >> operation;

    if (base < 2 || base > 16) {
        cout << "radix musi be from 2 to 16" << endl;
        return;
    }

    //perevodim v 10 systemu scisleniya
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
    int choise;
    while (true) {
        cout << "Enter thе case" << endl << endl;
        cout << "1. Convert a number from the decimal system to the r-th system" << endl;
        cout << "2. Convert a number from r-ary to decimal" << endl;
        cout << "3. Addition and multiplication of two numbers in the r-ary system" << endl;
        cout << "4. Completion of the program" << endl;
        cout << "Enter the program number without dot: ";
        cin >> choise;


        switch (choise) {
        case 1: {
            int base;
            double number;
            cout << "Enter the real number: ";
            cin >> number;

            cout << "Enter the base of the number system you want to convert to (2-16): ";
            cin >> base;

            if (base < 2 || base > 16) {
                cout << "North, the base must be between 2 and 16 " << endl;
                break;
            }

            //delim na zeluy i drobnuy chasti 
            int integerPart = (int)number;
            double fractionalPart = number - integerPart;

            string integerResult = integer_part(integerPart, base); //perevodim 
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
            cout << "End of programm" << endl;
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
