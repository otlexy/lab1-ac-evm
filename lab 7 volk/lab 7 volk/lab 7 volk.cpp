#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool isValidChar(char c, int base) {
    if (base <= 10) {
        return c >= '0' && c < ('0' + base);
    }
    else {
        return (c >= '0' && c <= '9') ||
            (c >= 'A' && c < ('A' + base - 10)) ||
            (c >= 'a' && c < ('a' + base - 10));
    }
}

bool isValidNumber(string num, int base) {
    for (int i = 0; i < num.length(); i++) {
        if (!isValidChar(num[i], base)) {
            return false;
        }
    }
    return true;
}

int charToValue(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

char valueToChar(int value) {
    if (value >= 0 && value <= 9) {
        return '0' + value;
    }
    else if (value >= 10 && value <= 15) {
        return 'A' + (value - 10);
    }
    return '?';
}

long long toDecimal(string num, int base) {
    long long decimal = 0;
    int power = 0;

    for (int i = num.length() - 1; i >= 0; i--) {
        int digitValue = charToValue(num[i]);
        decimal += digitValue * pow(base, power);
        power++;
    }

    return decimal;
}

string fromDecimal(long long decimal, int base) {
    if (decimal == 0) {
        return "0";
    }

    string result = "";

    while (decimal > 0) {
        int ostatok = decimal % base;
        result = valueToChar(ostatok) + result;
        decimal = decimal / base;
    }

    return result;
}

string inputNumber(int numberIndex, int& base) {
    string num;

    while (true) {
        cout << "Введите основание системы счисления для числа " << numberIndex << " (от 2 до 16): ";
        cin >> base;

        if (base < 2 || base > 16) {
            cout << "Ошибка! Основание должно быть от 2 до 16." << endl;
            continue;
        }

        cout << "Введите число " << numberIndex << " в системе с основанием " << base << ": ";
        cin >> num;

        if (isValidNumber(num, base)) {
            return num;
        }
        else {
            cout << "Число содержит недопустимые символы для системы с основанием " << base << "." << endl;
        }
    }
}

char chooseOperation() {
    char operation;

    cout << "\nВыберите операцию:" << endl;
    cout << "'+' - сложение" << endl;
    cout << "'-' - вычитание" << endl;
    cout << "'*' - умножение" << endl;
    cout << "'/' - деление" << endl;
    cout << "Ваш выбор: ";
    cin >> operation;

    return operation;
}

int chooseResultBase() {
    int base;

    while (true) {
        cout << "\nВведите основание системы счисления для результата (от 2 до 16): ";
        cin >> base;

        if (base >= 2 && base <= 16) {
            return base;
        }
        else {
            cout << "Основание должно быть от 2 до 16" << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== КАЛЬКУЛЯТОР ДЛЯ РАЗЛИЧНЫХ СИСТЕМ СЧИСЛЕНИЯ ===" << endl;

    int base1;
    string num1 = inputNumber(1, base1);

    int base2;
    string num2 = inputNumber(2, base2);

    char operation = chooseOperation();

    int resultBase = chooseResultBase();

    long long decimal1 = toDecimal(num1, base1);
    long long decimal2 = toDecimal(num2, base2);

    long long resultDecimal = 0;
    bool error = false;

    switch (operation) {
    case '+':
        resultDecimal = decimal1 + decimal2;
        break;

    case '-':
        resultDecimal = decimal1 - decimal2;
        break;

    case '*':
        resultDecimal = decimal1 * decimal2;
        break;

    case '/':
        if (decimal2 == 0) {
            cout << "Деление на ноль!!!" << endl;
            error = true;
        }
        else {
            resultDecimal = decimal1 / decimal2;
        }
        break;

    default:
        cout << "Неизвестная операция." << endl;
        error = true;
        break;
    }

    if (!error) {
        string result = fromDecimal(resultDecimal, resultBase);

        cout << "\n=== РЕЗУЛЬТАТ ===" << endl;
        cout << "Результат в системе с основанием " << resultBase << ": " << result << endl;
    }
}