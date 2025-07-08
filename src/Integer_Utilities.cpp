#include "Integer.hpp"
#include <ostream>


void Integer::normalize() {
    while (limbs.size() > 1 && limbs.back() == 0)
        limbs.pop_back();
    if (limbs.size() == 1 && limbs[0] == 0)
        isNegative = false;
}


std::string Integer::toString() const {
    if (limbs.empty()) return "0";

    Integer temp = *this;
    temp.isNegative = false;
    std::string result;
    Integer zero(0);
    Integer b(10);

    while (temp != zero) {
        Integer digit = temp % b;
        result = std::to_string(digit.limbs[0]) + result;
        temp /= b;
    }

    if (isNegative)
        result = "-" + result;

    return result.empty() ? "0" : result;
}

Integer Integer::abs() const {
    Integer result = *this;
    result.isNegative = false;
    return result;
}

// Returns the greatest common divisor of a and b
Integer Integer::gcd(const Integer& a, const Integer& b) {
    if (b < Integer(0) || a < Integer(0)) {
        throw std::invalid_argument("GCD is not defined for negative integers");
    }
    if (a == Integer(0)) return b.abs();
    if (b == Integer(0)) return a.abs();

    Integer x = a.abs();
    Integer y = b.abs();

    while (y != Integer(0)) {
        Integer r = x % y;
        x = y;
        y = r;
    }

    return x;
}

Integer Integer::lcm(const Integer& a, const Integer& b)  {
    if (a == Integer(0) || b == Integer(0)) return Integer(0);
    return (a.abs() * b.abs()) / gcd(a, b);
}


std::ostream& operator<<(std::ostream& os, const Integer& val) {
    return os << val.toString();
}