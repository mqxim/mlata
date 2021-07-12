#pragma once
#include "normalization.hpp"

struct NormalizedNumber
{
    float normalized;
    int exponent;
};

NormalizedNumber normalizeNumber(float number)
{
    NormalizedNumber numData;
    int exponent = 0;
    bool isNegative = (number < 0);
    if (isNegative)
    {
        number = number * -1;
    }

    if (number >= 10)
        while (number >= 10)
        {
            number = number / 10;
            exponent++;
        }
    else
        while (number < 1)
        {
            number = number * 10;
            exponent--;
        }
    numData.exponent = exponent;
    numData.normalized = isNegative ? number * -1 : number;
    return numData;   
}