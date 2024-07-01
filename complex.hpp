/**
 * @file complex.hpp
 * @brief Declaration of the Complex class for representing and manipulating complex numbers.
 * @date 2024-06-30
 * @version 1.0
 * @details
 * This file contains the declaration of the Complex class which provides functionalities for 
 * creating, manipulating, and performing arithmetic comparisons on complex numbers. It also 
 * includes methods for outputting the complex number to a stream.
 * 
 * Contact: wasimshebalny@gmail.com
 */

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <sstream>

/**
 * @class Complex
 * @brief A class to represent complex numbers.
 * 
 * This class provides methods for creating complex numbers, accessing their real and imaginary 
 * parts, comparing complex numbers, and outputting them as strings or to streams.
 */
class Complex {
public:
    /**
     * @brief Construct a new Complex object.
     * 
     * @param real The real part of the complex number.
     * @param imag The imaginary part of the complex number.
     */
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    /**
     * @brief Get the real part of the complex number.
     * 
     * @return double The real part of the complex number.
     */
    double get_real() const { return real; }

    /**
     * @brief Get the imaginary part of the complex number.
     * 
     * @return double The imaginary part of the complex number.
     */
    double get_imag() const { return imag; }

    /**
     * @brief Equality operator for comparing two complex numbers.
     * 
     * @param other The other complex number to compare with.
     * @return true If the complex numbers are equal.
     * @return false If the complex numbers are not equal.
     */
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    /**
     * @brief Inequality operator for comparing two complex numbers.
     * 
     * @param other The other complex number to compare with.
     * @return true If the complex numbers are not equal.
     * @return false If the complex numbers are equal.
     */
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    /**
     * @brief Less-than operator for comparing two complex numbers.
     * 
     * @param other The other complex number to compare with.
     * @return true If this complex number is less than the other.
     * @return false If this complex number is not less than the other.
     */
    bool operator<(const Complex& other) const {
        return real < other.real || (real == other.real && imag < other.imag);
    }

    /**
     * @brief Greater-than operator for comparing two complex numbers.
     * 
     * @param other The other complex number to compare with.
     * @return true If this complex number is greater than the other.
     * @return false If this complex number is not greater than the other.
     */
    bool operator>(const Complex& other) const {
        return real > other.real || (real == other.real && imag > other.imag);
    }

    /**
     * @brief Stream insertion operator for outputting a complex number to a stream.
     * 
     * @param os The output stream.
     * @param c The complex number to output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }

    /**
     * @brief Convert the complex number to a string representation.
     * 
     * @return std::string The string representation of the complex number.
     */
    std::string toString() const {
        std::ostringstream oss;
        oss << real << "+" << imag << "i";
        return oss.str();
    }

private:
    double real; ///< The real part of the complex number.
    double imag; ///< The imaginary part of the complex number.
};

#endif // COMPLEX_HPP
