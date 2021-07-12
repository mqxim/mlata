#include <iostream>
#include <string>
#include "normalization.hpp"
#include "stringOperations.hpp"

using namespace std;

// Задание номер 20 (первая лабораторная работа)
// Ильин Максим Олегович ПС-21
// 25.09.2018
// Составить программу перевода вещественного числа в форму
// константы с плавающей  точкой  в строковом формате. Целая часть
// мантиссы должна состоять из одной цифры (8).

struct NumberInfo
{
    string sign;
    string exponent;
    string digitsOfNumber;
};

string stringifyNormalizedNumber(float number)
{
    string result = "";
    while (number)
    {
        result = result + digitToString(number);
		number = number - int(number);
        number = number * 10;
    }
    return result;
}

NumberInfo initNumber(float number)
{
    NumberInfo data;
    
    bool isNegative = (number < 0);
    if (isNegative)
    {
        number = number * -1;
    }

    NormalizedNumber normalizedNumber = normalizeNumber(number);
    data.digitsOfNumber = stringifyNormalizedNumber(normalizedNumber.normalized);
    data.exponent = intToString(normalizedNumber.exponent);
    data.sign = isNegative ? "-" : "";
    return data;
}

string buildString(NumberInfo info)
{
    size_t strLength = info.digitsOfNumber.length();
    if (strLength == 0)
        return "";
    
    string result = info.sign;
    result = result + info.digitsOfNumber[0];

    if (strLength > 2)
    {
        result = result + '.';
        for (size_t i = 1; i < strLength; i++)
        {
            result = result + info.digitsOfNumber[i];
        }
    }
    result = result + 'E' + info.exponent;
    return result;
}

string floatToString(float number)
{
    if (number == 0)
    {
        return "0";
    }

    NumberInfo numInfo = initNumber(number);
    string result = buildString(numInfo);
    return result;
}

int main()
{
    float x = 1;
    while (x != 0)
    {
        cout << "Value: ";
        cin >> x;
        cout << floatToString(x) << " " << to_string(x) << endl << endl;
    }
    return 0;
}