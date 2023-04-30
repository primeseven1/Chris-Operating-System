#include <libc/math.h>

double floor(double value)
{
    if (value < 0.0 && value != (long)value)
        value--;

    return (double)(long)value;
}

double ceil(double value)
{
    if (value < 0)
        return (double)(long)value;

    return floor(value + 1);
}

int abs(int value) { return value < 0 ? value * -1 : value; }

double fabs(double value) { return value < 0 ? value * -1 : value; }