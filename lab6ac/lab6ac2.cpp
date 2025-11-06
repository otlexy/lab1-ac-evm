#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

using namespace std;

//функция возвращает целую часть числа
string do_zapyat(string number) {
    string do_zap;
    for (int i = 0; i < number.length(); i++) {
        if (number[i] == '.') {
            break;
        }
        do_zap += number[i];
    }
    return do_zap;
}

//функция возвращает дробную часть числа
string posle_zapyat(string number) {
    string posle_zap;
    bool found_dot = false;
    for (int i = 0; i < number.length(); i++) {
        if (number[i] == '.') {
            found_dot = true;
            continue;
        }
        if (found_dot) {
            posle_zap += number[i];
        }
    }
    return posle_zap;
}

//функция перевода из двоичной в десятичную СС
string bin_to_dec(string do_zap, string posle_zap) {
    long result1 = 0; //в эту переменную записывается результат перевода целой части числа
    int stepen1 = 1;
    for (int i = do_zap.length() - 1; i >= 0; i--) {
        result1 += (do_zap[i] - '0') * stepen1; //записывается результат перевода для цифры (перевод из типа char в int)
        stepen1 *= 2;
    } //цикл перевода из 2ой в 10ую для целой части
    double result2 = 0; //в эту переменную записывается результат перевода дробной части числа
    double stepen2 = 0.5;
    for (int i = 0; i < posle_zap.length(); i++) {
        result2 += (posle_zap[i] - '0') * stepen2;
        stepen2 /= 2;
    } //появляется лишний 0. при использовании to_string(result2) на типе double
    int temp = result2 * pow(10, posle_zap.length()); //переменная, чтобы убрать лишние '0' после запятой
    string bin_dec;
    if (result2 == 0) {
        bin_dec = to_string(result1);
    }
    else if (result1 == 0) {
        bin_dec = "0." + to_string(temp);
    }
    else {
        bin_dec = to_string(result1) + "." + to_string(temp);
    } //проверка разных случаев для числа
    return bin_dec;
}

//функция перевода из восьмеричной в десятичную СС
string oct_to_dec(string do_zap, string posle_zap) {
    int result1 = 0;
    int stepen1 = 1;
    for (int i = do_zap.length() - 1; i >= 0; i--) {
        result1 += (do_zap[i] - '0') * stepen1;
        stepen1 *= 8;
    }
    double result2 = 0;
    double stepen2 = 0.125;
    for (int i = 0; i < posle_zap.length(); i++) {
        result2 += (posle_zap[i] - '0') * stepen2;
        stepen2 /= 8;
    }
    int temp = result2 * pow(10, posle_zap.length());
    string oct_dec; //окончательный результат перевода из 8ой в 10ую
    if (result2 == 0) {
        oct_dec = to_string(result1);
    }
    else if (result1 == 0) {
        oct_dec = "0." + to_string(temp);
    }
    else {
        oct_dec = to_string(result1) + "." + to_string(temp);
    }
    return oct_dec;
}

//функция перевода из шестнадцатеричной в десятичную СС
string hex_to_dec(string do_zap, string posle_zap) {
    int result1 = 0;
    int stepen1 = 1;
    for (int i = do_zap.length() - 1; i >= 0; i--) {
        int digit;
        if (do_zap[i] == 'A') {
            digit = 10;
        }
        else if (do_zap[i] == 'B') {
            digit = 11;
        }
        else if (do_zap[i] == 'C') {
            digit = 12;
        }
        else if (do_zap[i] == 'D') {
            digit = 13;
        }
        else if (do_zap[i] == 'E') {
            digit = 14;
        }
        else if (do_zap[i] == 'F') {
            digit = 15;
        } //проверка условий для цифр 'A', 'B' ... 'F' и последующий их перевод для 10ой СС
        else {
            digit = do_zap[i] - '0'; //преобразование знака из char в int
        }
        result1 += digit * stepen1;
        stepen1 *= 16;
    }

    double result2 = 0;
    double stepen2 = 0.0625;
    for (int i = 0; i < posle_zap.length(); i++) {
        int digit;
        if (posle_zap[i] == 'A') {
            digit = 10;
        }
        else if (posle_zap[i] == 'B') {
            digit = 11;
        }
        else if (posle_zap[i] == 'C') {
            digit = 12;
        }
        else if (posle_zap[i] == 'D') {
            digit = 13;
        }
        else if (posle_zap[i] == 'E') {
            digit = 14;
        }
        else if (posle_zap[i] == 'F') {
            digit = 15;
        }
        else {
            digit = posle_zap[i] - '0';
        }
        result2 += digit * stepen2;
        stepen2 /= 16;
    }
    int temp = result2 * pow(10, posle_zap.length());
    string hex_dec; //окончательный результат перевода из 16ой в 10ую
    if (result2 == 0) {
        hex_dec = to_string(result1);
    }
    else if (result1 == 0) {
        hex_dec = "0." + to_string(temp);
    }
    else {
        hex_dec = to_string(result1) + "." + to_string(temp);
    }
    return hex_dec;
}

int main() {
    string number;
    int CI;
    setlocale(LC_ALL, "Russian");
    cout << "Введите число: ";
    cin >> number;
    cout << "Введите систему счисления числа: ";
    cin >> CI;
    if (CI == 2) {
        string celaya = do_zapyat(number);
        string drobnaya = posle_zapyat(number);
        cout << "Число в десятичной СС " << bin_to_dec(celaya, drobnaya);
    } //если вводимое число в 2ой СС
    else if (CI == 8) {
        string celaya = do_zapyat(number);
        string drobnaya = posle_zapyat(number);
        cout << "Число в десятичной СС " << oct_to_dec(celaya, drobnaya);
    } //если вводимое число в 8ой СС
    else if (CI == 16) {
        string celaya = do_zapyat(number);
        string drobnaya = posle_zapyat(number);
        cout << "Число в десятичной СС " << hex_to_dec(celaya, drobnaya);
    } //если вводимое число в 16ой СС
    else {
        cout << "Такая система счисления не предусмотрена";
    }
}
