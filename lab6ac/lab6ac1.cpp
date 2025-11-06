#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

//перевод целой части в двоичную систему
string dec_to_bin_do(int integer) {
    string result = "";
    while (integer > 0) {
        result = to_string(integer % 2) + result;
        integer /= 2;
    } //заполняется строка result с первого элемента
    return result;
}

//перевод дробной части в двоичную систему
string dec_to_bin_posle(double fractional) {
    string result = "";
    for (int i = 0; fractional > 0; i++) {
        fractional *= 2;
        if (fractional >= 1) {
            result += "1";
            fractional -= 1;
        }
        else {
            result += "0";
        } //с конца заполняется часть после запятой
    }
    return result;
}

//перевод целой части в восьмеричную систему
string dec_to_oct_do(int integer) {
    string result = "";
    while (integer > 0) {
        result = to_string(integer % 8) + result;
        integer /= 8;
    }
    return result;
}

//перевод дробной части в восьмеричную систему
string dec_to_oct_posle(double fractional) {
    string result = "";
    for (int i = 0; fractional > 0; i++) {
        fractional *= 8;
        int digit = (int)fractional; //записывается целую часть от умножения
        result += to_string(digit);
        fractional -= digit; //отнимается целая часть для продолжения работы с дробной частью
    }
    return result;
}

//перевод целой части в шестнадцатеричную систему
string dec_to_hex_do(int integer) {
    string result = "";
    while (integer > 0) {
        if (integer % 16 == 10) {
            result = 'A' + result;
        }
        else if (integer % 16 == 11) {
            result = 'B' + result;
        }
        else if (integer % 16 == 12) {
            result = 'C' + result;
        }
        else if (integer % 16 == 13) {
            result = 'D' + result;
        }
        else if (integer % 16 == 14) {
            result = 'E' + result;
        }
        else if (integer % 16 == 15) {
            result = 'F' + result;
        } //проверка остатка на >= 10
        else {
            result = to_string(integer % 16) + result;
        }
        integer /= 16;
    }
    return result;
}

//перевод дробной части в шестнадцатеричную систему
string dec_to_hex_posle(double fractional) {
    string result = "";
    for (int i = 0; fractional > 0; i++) {
        fractional *= 16;
        int digit = int(fractional);
        if (digit == 10) {
            result += 'A';
        }
        else if (digit == 11) {
            result += 'B';
        }
        else if (digit == 12) {
            result += 'C';
        }
        else if (digit == 13) {
            result += 'D';
        }
        else if (digit == 14) {
            result += 'E';
        }
        else if (digit == 15) {
            result += 'F';
        }
        else {
            result += to_string(digit);
        }
        fractional -= digit;
    }
    return result;
}

int main() {
    double number;
    setlocale(LC_ALL, "Russian");
    cout << "Введите число в десятичной системе счисления: ";
    cin >> number;
    int integer = int(number); //целая часть
    double fractional = number - integer; //дробная часть
    string binary, octal, hex; //строки, в которые будет записываться ответ

    //запись окончательных переводов в различные системы счисления
    if (fractional == 0) {
        binary = dec_to_bin_do(integer);
        octal = dec_to_oct_do(integer);
        hex = dec_to_hex_do(integer);
    }
    else {
        binary = dec_to_bin_do(integer) + '.' + dec_to_bin_posle(fractional);
        octal = dec_to_oct_do(integer) + '.' + dec_to_oct_posle(fractional);
        hex = dec_to_hex_do(integer) + '.' + dec_to_hex_posle(fractional);
    }

    //вывод ответа
    cout << "Двоичная СС:  " << binary << '\n';
    cout << "Восьмеричная СС: " << octal << '\n';
    cout << "Шестнадцатеричная СС: " << hex << '\n';
}