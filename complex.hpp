#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    double get_real() const { return real; }
    double get_imag() const { return imag; }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator<(const Complex& other) const {
        return real < other.real || (real == other.real && imag < other.imag);
    }

    bool operator>(const Complex& other) const {
        return real > other.real || (real == other.real && imag > other.imag);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }

private:
    double real;
    double imag;
};

#endif // COMPLEX_HPP
