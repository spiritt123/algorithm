#pragma once

#include <istream>
#include <ostream>

class ComplexNumber
{
public:
    ComplexNumber();
    ComplexNumber(double re, double im);
    ~ComplexNumber();

    ComplexNumber& operator=(const ComplexNumber& number);
    friend const ComplexNumber operator+(ComplexNumber& left, const ComplexNumber& right);
    friend const ComplexNumber operator-(ComplexNumber& left, const ComplexNumber& right);
    friend const ComplexNumber operator*(ComplexNumber& left, const ComplexNumber& right);
    friend const ComplexNumber operator/(ComplexNumber& left, const ComplexNumber& right);

    friend ComplexNumber& operator+=(ComplexNumber& left, const ComplexNumber& right);
    friend ComplexNumber& operator-=(ComplexNumber& left, const ComplexNumber& right);
    friend ComplexNumber& operator*=(ComplexNumber& left, const ComplexNumber& right);
    friend ComplexNumber& operator/=(ComplexNumber& left, const ComplexNumber& right);

    friend bool operator==(ComplexNumber& left, const ComplexNumber& right);

    double abs(ComplexNumber& number);
    ComplexNumber& pow(ComplexNumber& number, int power);
    friend std::ostream& operator<<(std::ostream &os, const ComplexNumber& number);
public:
    double re, im;
};

