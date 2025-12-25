#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// ЕДИНСТВЕННАЯ ФУНКЦИЯ ВНЕ MAIN
string convertNumber(const string& number, int cc1, int cc2) {
    if (cc1 < 2 || cc1 > 16 || cc2 < 2 || cc2 > 16) {
        return "ERROR";
    }
    if (number.empty()) {
        return "ERROR";
    }

    // Обработка знака
    bool isNegative = false;
    string num = number;
    if (num[0] == '-') {
        isNegative = true;
        num = num.substr(1);
        if (num.empty()) {
            return "ERROR";
        }
    }

    // Поиск точки
    size_t dotPos = string::npos;
    for (size_t i = 0; i < num.length(); i++) {
        if (num[i] == '.') {
            dotPos = i;
            break;
        }
    }

    string integerPart, fractionalPart;
    if (dotPos != string::npos) {
        integerPart = num.substr(0, dotPos);
        fractionalPart = num.substr(dotPos + 1);
    }
    else {
        integerPart = num;
        fractionalPart = "";
    }

    if (integerPart.empty()) {
        integerPart = "0";
    }

    // Перевод целой части в десятичную
    long long integerDecimal = 0;
    long long power = 1;
    for (int i = integerPart.length() - 1; i >= 0; i--) {
        char c = integerPart[i];
        int digitValue;

        if (c >= '0' && c <= '9') {
            digitValue = c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            digitValue = 10 + (c - 'A');
        }
        else if (c >= 'a' && c <= 'f') {
            digitValue = 10 + (c - 'a');
        }
        else {
            return "ERROR";
        }

        if (digitValue >= cc1) {
            return "ERROR";
        }

        integerDecimal += digitValue * power;
        power *= cc1;
    }

    // Перевод дробной части в десятичную
    double fractionalDecimal = 0.0;
    if (!fractionalPart.empty()) {
        double fracPower = 1.0 / cc1;
        for (size_t i = 0; i < fractionalPart.length(); i++) {
            char c = fractionalPart[i];
            int digitValue;

            if (c >= '0' && c <= '9') {
                digitValue = c - '0';
            }
            else if (c >= 'A' && c <= 'F') {
                digitValue = 10 + (c - 'A');
            }
            else if (c >= 'a' && c <= 'f') {
                digitValue = 10 + (c - 'a');
            }
            else {
                return "ERROR";
            }

            if (digitValue >= cc1) {
                return "ERROR";
            }

            fractionalDecimal += digitValue * fracPower;
            fracPower /= cc1;
        }
    }

    double decimalValue = integerDecimal + fractionalDecimal;
    if (isNegative) {
        decimalValue = -decimalValue;
    }

    // Обработка нуля
    if (decimalValue < 1e-10 && decimalValue > -1e-10) {
        return "0";
    }

    // Подготовка к обратному переводу
    bool resultNegative = false;
    double absVal = decimalValue;
    if (decimalValue < 0) {
        resultNegative = true;
        absVal = -absVal;
    }

    // Целая часть результата
    long long intPart = (long long)absVal;
    string resultInt = "";
    if (intPart == 0) {
        resultInt = "0";
    }
    else {
        while (intPart > 0) {
            int rem = intPart % cc2;
            char ch;
            if (rem < 10) {
                ch = '0' + rem;
            }
            else {
                ch = 'A' + (rem - 10);
            }
            resultInt = ch + resultInt;
            intPart /= cc2;
        }
    }

    // Дробная часть результата
    string resultFrac = "";
    double fracPart = absVal - (long long)absVal;
    if (fracPart > 1e-10) {
        resultFrac = ".";
        int precision = 0;
        const int MAX_PREC = 10;
        while (fracPart > 1e-10 && precision < MAX_PREC) {
            fracPart *= cc2;
            int digit = (int)fracPart;
            char ch;
            if (digit < 10) {
                ch = '0' + digit;
            }
            else {
                ch = 'A' + (digit - 10);
            }
            resultFrac += ch;
            fracPart -= digit;
            precision++;
        }
    }

    string result = resultInt + resultFrac;
    if (resultNegative) {
        result = "-" + result;
    }

    return result;
}

// ОСНОВНАЯ ПРОГРАММА
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== КАЛЬКУЛЯТОР СИСТЕМ СЧИСЛЕНИЯ ===" << endl;
    cout << "Поддержка: основания 2–16, дробные (через точку), отрицательные (через '-')\n" << endl;

    // --- Ввод первого числа ---
    string num1;
    int base1;
    while (true) {
        cout << "Введите основание первого числа (2–16): ";
        cin >> base1;
        if (base1 >= 2 && base1 <= 16) break;
        cout << "Ошибка: основание должно быть от 2 до 16.\n";
    }
    cout << "Введите первое число: ";
    cin >> num1;
    if (convertNumber(num1, base1, 10) == "ERROR") {
        cout << "Ошибка: некорректное число для указанной системы.\n";
        return 1;
    }

    // --- Ввод второго числа ---
    string num2;
    int base2;
    while (true) {
        cout << "Введите основание второго числа (2–16): ";
        cin >> base2;
        if (base2 >= 2 && base2 <= 16) break;
        cout << "Ошибка: основание должно быть от 2 до 16.\n";
    }
    cout << "Введите второе число: ";
    cin >> num2;
    if (convertNumber(num2, base2, 10) == "ERROR") {
        cout << "Ошибка: некорректное число для указанной системы.\n";
        return 1;
    }

    // --- Выбор операции ---
    char op;
    cout << "Выберите операцию (+, -, *, /): ";
    cin >> op;
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        cout << "Ошибка: неизвестная операция.\n";
        return 1;
    }

    // --- Основание результата ---
    int resBase;
    while (true) {
        cout << "Введите основание для результата (2–16): ";
        cin >> resBase;
        if (resBase >= 2 && resBase <= 16) break;
        cout << "Ошибка: основание должно быть от 2 до 16.\n";
    }

    // --- Перевод в десятичную систему ---
    string dec1Str = convertNumber(num1, base1, 10);
    string dec2Str = convertNumber(num2, base2, 10);


    double d1 = stod(dec1Str);
    double d2 = stod(dec2Str);

    // --- Выполнение операции ---
    double resultDec;
    bool error = false;

    if (op == '+') {
        resultDec = d1 + d2;
    }
    else if (op == '-') {
        resultDec = d1 - d2;
    }
    else if (op == '*') {
        resultDec = d1 * d2;
    }
    else if (op == '/') {
        if (d2 > -1e-12 && d2 < 1e-12) {
            cout << "Ошибка: деление на ноль!\n";
            error = true;
        }
        else {
            resultDec = d1 / d2;
        }
    }

    if (error) {
        return 1;
    }

    // --- Преобразуем результат в строку десятичного числа ---
    string resultStr;
    if (resultDec == 0.0 || (resultDec < 1e-10 && resultDec > -1e-10)) {
        resultStr = "0";
    }
    else {
        bool neg = false;
        double x = resultDec;
        if (x < 0) {
            neg = true;
            x = -x;
        }

        // Целая часть
        long long ip = (long long)x;
        string intPart = "";
        if (ip == 0) {
            intPart = "0";
        }
        else {
            long long tmp = ip;
            while (tmp > 0) {
                intPart = char('0' + (tmp % 10)) + intPart;
                tmp /= 10;
            }
        }

        // Дробная часть (6 знаков как в to_string)
        string fracPart = "";
        double fp = x - ip;
        if (fp > 1e-10) {
            for (int i = 0; i < 6; i++) {
                fp *= 10;
                int digit = (int)fp;
                fracPart += char('0' + digit);
                fp -= digit;
            }
            // Убрать конечные нули
            while (!fracPart.empty() && fracPart[fracPart.length() - 1] == '0') {
                fracPart = fracPart.substr(0, fracPart.length() - 1);
            }
        }

        resultStr = intPart;
        if (!fracPart.empty()) {
            resultStr += "." + fracPart;
        }
        if (neg) {
            resultStr = "-" + resultStr;
        }
    }

    // --- Перевод результата в целевую систему ---
    string finalResult = convertNumber(resultStr, 10, resBase);

    if (finalResult == "ERROR") {
        cout << "Ошибка при конвертации результата!\n";
        return 1;
    }

    // --- Вывод ---
    cout << "\n=== РЕЗУЛЬТАТ ===" << endl;
    cout << num1 << " (" << base1 << ") " << op << " "
        << num2 << " (" << base2 << ") = "
        << finalResult << " (" << resBase << ")" << endl;

    return 0;
}