#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <locale>

using namespace std;

// Функция перевода числа из системы cc1 в cc2
string convertNumber(const string& number, int cc1, int cc2) {
    if (cc1 < 2 || cc1 > 16 || cc2 < 2 || cc2 > 16) {
        return "ERROR";
    }
    if (number.empty()) {
        return "ERROR";
    }

    bool isNegative = false;
    string num = number;
    if (num[0] == '-') {
        isNegative = true;
        num = num.substr(1);
        if (num.empty()) {
            return "ERROR";
        }
    }

    size_t dotPos = num.find('.');
    string integerPart = (dotPos == string::npos) ? num : num.substr(0, dotPos);
    string fractionalPart = (dotPos == string::npos) ? "" : num.substr(dotPos + 1);

    if (integerPart.empty()) {
        integerPart = "0";
    }

    // Целая часть → в десятичную
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

    // Дробная часть → в десятичную
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
    if (abs(decimalValue) < 1e-12) {
        return "0";
    }

    // --- Особый случай: перевод в десятичную систему ---
    if (cc2 == 10) {
        ostringstream oss;
        oss.imbue(locale::classic());
        oss << fixed << setprecision(10) << decimalValue;
        string res = oss.str();

        // Удаление лишних нулей после точки
        size_t dot = res.find('.');
        if (dot != string::npos) {
            size_t lastNonZero = res.find_last_not_of('0');
            if (lastNonZero == dot) {
                res.erase(dot);
            }
            else if (lastNonZero != string::npos) {
                res.erase(lastNonZero + 1);
            }
        }
        if (res == "-0") res = "0";
        return res;
    }

    // --- Общий случай: cc2 != 10 ---
    bool resultNegative = (decimalValue < 0);
    double absVal = abs(decimalValue);

    // Целая часть результата
    long long intPart = (long long)absVal;
    string resultInt = (intPart == 0) ? "0" : "";
    long long tmp = intPart;
    if (tmp > 0) {
        while (tmp > 0) {
            int rem = tmp % cc2;
            char ch = (rem < 10) ? ('0' + rem) : ('A' + rem - 10);
            resultInt = ch + resultInt;
            tmp /= cc2;
        }
    }

    // Дробная часть результата
    string resultFrac = "";
    double fracPart = absVal - (long long)absVal;
    if (fracPart > 1e-12) {
        resultFrac = ".";
        int precision = 0;
        const int MAX_PREC = 10;
        while (fracPart > 1e-12 && precision < MAX_PREC) {
            fracPart *= cc2;
            int digit = (int)fracPart;
            char ch = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
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

// Надёжное преобразование строки в double с точкой как разделителем
double safeStod(const string& s) {
    istringstream iss(s);
    iss.imbue(locale::classic());
    double val;
    iss >> val;
    return val;
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

    double d1 = safeStod(dec1Str);
    double d2 = safeStod(dec2Str);

    // --- Выполнение операции ---
    double resultDec;
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
        if (abs(d2) < 1e-12) {
            cout << "Ошибка: деление на ноль!\n";
            return 1;
        }
        resultDec = d1 / d2;
    }

    // --- Преобразуем результат в строку с 10 знаками после запятой ---
    string resultStr;
    if (abs(resultDec) < 1e-12) {
        resultStr = "0";
    }
    else {
        ostringstream oss;
        oss.imbue(locale::classic());
        oss << fixed << setprecision(10) << resultDec;
        resultStr = oss.str();

        // Удаление лишних нулей
        size_t dotPos = resultStr.find('.');
        if (dotPos != string::npos) {
            size_t lastNonZero = resultStr.find_last_not_of('0');
            if (lastNonZero == dotPos) {
                resultStr.erase(dotPos);
            }
            else if (lastNonZero != string::npos) {
                resultStr.erase(lastNonZero + 1);
            }
        }
        if (resultStr == "-0") resultStr = "0";
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