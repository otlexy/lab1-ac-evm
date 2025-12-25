#include <iostream>
#include <string>
using namespace std;

// ФУНКЦИЯ ПОЛУЧАЕТ ЦИФРОВОЕ ЗНАЧЕНИЕ СИМВОЛА:
// например, '0' → 0, 'A' или 'a' → 10, 'F' или 'f' → 15 и т.д.
int getDigitValue(char c)
{
    // Создаём массив со всеми возможными цифрами в системах счисления до 16-ричной
    char digits[] = "0123456789ABCDEF"; // 16 символов: от 0 до F

    // Проходим по каждому символу в массиве digits
    for (int i = 0; i < 16; i++) // от 0 до 15 включительно
    {
        // Если нашли совпадение с верхним регистром (например, 'A')
        if (c == digits[i])
        {
            return i; // возвращаем его номер — это и есть его числовое значение
        }

    }

    // Если символ неизвестный (например, 'G'), возвращаем 0
    return 0;
}

// ФУНКЦИЯ ПЕРЕВОДИТ ЦЕЛОЕ ЧИСЛО ИЗ ДЕСЯТИЧНОЙ СИСТЕМЫ В ДРУГУЮ (от 2 до 16)
string decimalIntegerToBase(int number, int base)
{
    // Если число 0 — сразу возвращаем "0"
    if (number == 0)
    {
        return "0";
    }

    // Создаём пустую строку для результата
    string result = "";

    // Повторяем, пока число не станет 0
    while (number > 0)
    {
        // Находим остаток от деления на основание системы (например, 617 % 2 = 1)
        int remainder = number % base;

        // Делим число нацело на основание (например, 617 / 2 = 308)
        number = number / base;

        // Это "таблица" цифр — индекс соответствует числу: 0→'0', 10→'A' и т.д.
        char digits[] = "0123456789ABCDEF";

        // Берём нужную цифру из таблицы
        char digit = digits[remainder]; // например, remainder=10 → digit='A'

        // Добавляем цифру в конец строки (но цифры получаются в обратном порядке!)
        result = result + digit;
    }

    // Теперь "переворачиваем" строку, потому что цифры шли в обратном порядке
    string reversed = "";
    for (int i = result.length() - 1; i >= 0; i--) // идём с конца к началу
    {
        reversed = reversed + result[i];
    }

    // Возвращаем перевёрнутую строку
    return reversed;
}

// ФУНКЦИЯ ПЕРЕВОДИТ ДРОБНУЮ ЧАСТЬ ЧИСЛА ИЗ ДЕСЯТИЧНОЙ СИСТЕМЫ В ДРУГУЮ
// (например, 0.25 → в двоичную → "01", потому что 0.25 = 0×0.5 + 1×0.25)
string decimalFractionToBase(double fraction, int base)
{
    // Если дробная часть 0 — возвращаем "0"
    if (fraction == 0.0)
    {
        return "0";
    }

    // Создаём пустую строку для результата
    string result = "";
    int count = 0;

    // Повторяем, пока дробная часть не станет 0
    while (fraction > 0)
    {
        // Умножаем дробную часть на основание системы
        fraction = fraction * base; // например: 0.82 * 2 = 1.64

        // Берём ЦЕЛУЮ часть — это будет очередная цифра результата
        int integerPart = (int)fraction; // (int)1.64 → 1

        // Таблица цифр
        char digits[] = "0123456789ABCDEF";

        // Берём символ по индексу
        char digit = digits[integerPart];

        // Добавляем его к результату
        result = result + digit;

        // Вычитаем целую часть, оставляя только дробную
        fraction = fraction - integerPart; // 1.64 - 1 = 0.64

        // Увеличиваем счётчик цифр
        count++;
    }

    // Возвращаем строку с цифрами после запятой
    return result;
}

// ФУНКЦИЯ РАЗДЕЛЯЕТ ЧИСЛО НА ЦЕЛУЮ И ДРОБНУЮ ЧАСТЬ ПО ТОЧКЕ
// например: "123.45" → integerPart = "123", fractionPart = "45"
void splitNumber(string number, string& integerPart, string& fractionPart) //строка объявляет функцию, которая берёт строку с числом, и по ссылкам заполняет две другие строки — целой и дробной частью этого числа
{
    // Очищаем строки на всякий случай
    integerPart = "";
    fractionPart = "";

    // Флаг: нашли ли мы точку?
    bool foundDot = false;

    // Проходим по каждому символу строки
    for (int i = 0; i < number.length(); i++)
    {
        char c = number[i]; // текущий символ

        // Если символ — точка
        if (c == '.')
        {
            foundDot = true;
            continue; // пропускаем точку, не добавляем её никуда
        }

        // Если точка ещё не была найдена — символ идёт в целую часть
        if (!foundDot)
        {
            integerPart = integerPart + c;
        }
        // Если точка уже найдена — символ идёт в дробную часть
        else
        {
            fractionPart = fractionPart + c;
        }
    }

    // Если точка была, но после неё ничего нет → дробная часть ""
    // Например, "123." → integerPart="123", fractionPart=""
}

// ПЕРЕВОДИМ ДВОИЧНОЕ ЧИСЛО В ДЕСЯТИЧНОЕ
double binaryToDecimal(string binary)
{
    // Разделяем на целую и дробную части
    string integerPart, fractionPart;
    splitNumber(binary, integerPart, fractionPart);

    // --- Перевод целой части ---
    int integerResult = 0;
    int power = 1; // начинаем с 2^0 = 1

    // Идём справа налево (от младшего разряда к старшему)
    for (int i = integerPart.length() - 1; i >= 0; i--)
    {
        char c = integerPart[i];

        if (c == '1') // если бит = 1
        {
            integerResult = integerResult + power; // добавляем текущую степень двойки
        }
        // если '0' — ничего не делаем

        power = power * 2; // переходим к следующей степени двойки: 1 → 2 → 4 → 8...
    }

    // --- Перевод дробной части ---
    double fractionResult = 0.0;
    double fractionPower = 0.5; // первая дробная степень: 2^(-1) = 0.5

    // Идём слева направо (первая цифра после точки — это 0.5, вторая — 0.25 и т.д.)
    for (int i = 0; i < fractionPart.length(); i++)
    {
        char c = fractionPart[i];

        if (c == '1')
        {
            fractionResult = fractionResult + fractionPower;
        }

        fractionPower = fractionPower / 2.0; // следующая степень: 0.5 → 0.25 → 0.125...
    }

    // Возвращаем сумму целой и дробной частей
    return integerResult + fractionResult;
}

// ПЕРЕВОДИМ ВОСЬМЕРИЧНОЕ ЧИСЛО В ДЕСЯТИЧНОЕ
double octalToDecimal(string octal)
{
    string integerPart, fractionPart;
    splitNumber(octal, integerPart, fractionPart);

    // --- Целая часть: умножаем каждую цифру на 8^позиция ---
    int integerResult = 0;
    int power = 1; // 8^0 = 1

    for (int i = integerPart.length() - 1; i >= 0; i--)
    {
        char c = integerPart[i];
        int value = getDigitValue(c); // получаем 0..7 из символа '0'..'7'

        integerResult = integerResult + value * power;

        power = power * 8; // 1 → 8 → 64 → 512...
    }

    // --- Дробная часть ---
    double fractionResult = 0.0;
    double fractionPower = 1.0 / 8.0; // 8^(-1) = 0.125

    for (int i = 0; i < fractionPart.length(); i++)
    {
        char c = fractionPart[i];
        int value = getDigitValue(c);

        fractionResult = fractionResult + value * fractionPower;

        fractionPower = fractionPower / 8.0; // 0.125 → 0.015625 → ...
    }

    return integerResult + fractionResult;
}

// ПЕРЕВОДИМ ШЕСТНАДЦАТЕРИЧНОЕ ЧИСЛО В ДЕСЯТИЧНОЕ
double hexToDecimal(string hex)
{
    string integerPart, fractionPart;
    splitNumber(hex, integerPart, fractionPart);

    // --- Целая часть ---
    int integerResult = 0;
    int power = 1; // 16^0 = 1

    for (int i = integerPart.length() - 1; i >= 0; i--)
    {
        char c = integerPart[i];
        int value = getDigitValue(c); // 'A' → 10, 'F' → 15 и т.д.

        integerResult = integerResult + value * power;

        power = power * 16; // 1 → 16 → 256 → 4096...
    }

    // --- Дробная часть ---
    double fractionResult = 0.0;
    double fractionPower = 1.0 / 16.0; // 16^(-1) = 0.0625

    for (int i = 0; i < fractionPart.length(); i++)
    {
        char c = fractionPart[i];
        int value = getDigitValue(c);

        fractionResult = fractionResult + value * fractionPower;

        fractionPower = fractionPower / 16.0; // 0.0625 → 0.00390625 → ...
    }

    return integerResult + fractionResult;
}

// ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ
int main()
{
    // Включаем поддержку русского языка в консоли (на Windows)
    setlocale(LC_ALL, "Russian");

    // Заголовок
    cout << "РЕШЕНИЕ ЗАДАНИЯ ПО СИСТЕМАМ СЧИСЛЕНИЯ" << endl;

    // ЗАДАНИЕ 1: Перевод из десятичной системы в другие

    cout << "\n1. ПЕРЕВОД ИЗ ДЕСЯТИЧНОЙ СИСТЕМЫ В ДРУГИЕ:" << endl;

    // а) Число 167
    cout << "\nа) Число 167 (10):" << endl;
    cout << "Двоичная (2):      " << decimalIntegerToBase(167, 2) << " (2)" << endl;
    cout << "Восьмеричная (8):  " << decimalIntegerToBase(167, 8) << " (8)" << endl;
    cout << "Шестнадцатеричная (16): " << decimalIntegerToBase(167, 16) << " (16)" << endl;

    // б) Число 113
    cout << "\nб) Число 597 (10):" << endl;
    cout << "Двоичная (2):      " << decimalIntegerToBase(113, 2) << " (2)" << endl;
    cout << "Восьмеричная (8):  " << decimalIntegerToBase(113, 8) << " (8)" << endl;
    cout << "Шестнадцатеричная (16): " << decimalIntegerToBase(113, 16) << " (16)" << endl;

    // в) Число 607,5 — целая и дробная части
    cout << "\nв) Число 412.25 (10):" << endl;
    string intPart607_2 = decimalIntegerToBase(607, 2);
    string fracPart607_2 = decimalFractionToBase(5, 2);
    cout << "Двоичная:      " << intPart607_2 << "." << fracPart607_2 << " (2)" << endl;

    string intPart607_8 = decimalIntegerToBase(607, 8);
    string fracPart607_8 = decimalFractionToBase(5, 8);
    cout << "Восьмеричная:  " << intPart607_8 << "." << fracPart607_8 << " (8)" << endl;

    string intPart607_16 = decimalIntegerToBase(607, 16);
    string fracPart607_16 = decimalFractionToBase(5, 16);
    cout << "Шестнадцатеричная: " << intPart607_16 << "." << fracPart607_16 << " (16)" << endl;

    // г) Число 828,25
    cout << "\nг) Число 828,25 (10):" << endl;
    cout << "Двоичная:      " << decimalIntegerToBase(828, 2) << "." << decimalFractionToBase(25, 2) << " (2)" << endl;
    cout << "Восьмеричная:  " << decimalIntegerToBase(828, 8) << "." << decimalFractionToBase(25, 8) << " (8)" << endl;
    cout << "Шестнадцатеричная: " << decimalIntegerToBase(828, 16) << "." << decimalFractionToBase(25, 16) << " (16)" << endl;

    // д) Число 314.71
    cout << "\nд) Число 84.82 (10):" << endl;
    cout << "Двоичная:      " << decimalIntegerToBase(314, 2) << "." << decimalFractionToBase(71, 2) << " (2)" << endl;
    cout << "Восьмеричная:  " << decimalIntegerToBase(314, 8) << "." << decimalFractionToBase(71, 8) << " (8)" << endl;
    cout << "Шестнадцатеричная: " << decimalIntegerToBase(314, 16) << "." << decimalFractionToBase(71, 16) << " (16)" << endl;

    // ЗАДАНИЕ 2: Перевод в десятичную систему

    cout << "\n\n2. ПЕРЕВОД В ДЕСЯТИЧНУЮ СИСТЕМУ ИЗ ДРУГИХ СИСТЕМ:" << endl;

    // а) Двоичное 110010001
    double res_a = binaryToDecimal("110010001");
    cout << "\nа) Двоичное число 110010001 (2):" << endl;
    cout << "В десятичной: " << res_a << " (10)" << endl;

    // б) Двоичное 100100000
    double res_b = binaryToDecimal("100100000");
    cout << "\nб) Двоичное число 100100000 (2):" << endl;
    cout << "В десятичной: " << res_b << " (10)" << endl;

    // в) Двоичное 1110011100,111
    double res_c = binaryToDecimal("1110011100.111");
    cout << "\nв) Двоичное число 1110011100.111 (2):" << endl;
    cout << "В десятичной: " << res_c << " (10)" << endl;

    // г) Двоичное 1010111010.1110111
    double res_d = binaryToDecimal("1010111010.1110111");
    cout << "\nг) Двоичное число 1010111010.1110111 (2):" << endl;
    cout << "В десятичной: " << res_d << " (10)" << endl;

    // д) Восьмеричное 704.6
    double res_e = octalToDecimal("704.6");
    cout << "\nд) Восьмеричное число 704.6 (8):" << endl;
    cout << "В десятичной: " << res_e << " (10)" << endl;

    // е) Шестнадцатеричное 367.38
    double res_f = hexToDecimal("367.38");
    cout << "\nе) Шестнадцатеричное число 367.38 (16):" << endl;
    cout << "В десятичной: " << res_f << " (10)" << endl;

    return 0;
}