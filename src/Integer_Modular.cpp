#include "Integer.hpp"
#include <stdexcept>
#include <tuple>


static std::tuple<Integer, Integer, Integer> extended_gcd(const Integer& a, const Integer& b) {
    Integer old_r = a, r = b;
    Integer old_s = Integer(1), s = Integer(0);
    Integer old_t = Integer(0), t = Integer(1);

    while (r != Integer(0)) {
        Integer quotient = old_r / r;

        Integer temp = r;
        r = old_r - quotient * r;
        old_r = temp;

        temp = s;
        s = old_s - quotient * s;
        old_s = temp;

        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }

    return {old_r, old_s, old_t};
}

// Returns x such that (a * x) % m == 1
Integer mod_inverse(const Integer& a, const Integer& m) {
    Integer nonneg_a = a;
    if (m == Integer(0)) {
        throw std::invalid_argument("Modulus must be non-zero");
    }
    if (m == Integer(1)) {
        return Integer(0); // Inverse of any number mod 1 is 0
    }
    if (a == Integer(0)) {
        throw std::invalid_argument("Inverse does not exist for zero");
    }
    if (a < Integer(0) ) {
        nonneg_a = -a; // Ensure a is non-negative
    }
    if (m < Integer(0)) {
        throw std::invalid_argument("Modulus must be greater than zero");
    }
    if (Integer::gcd(a, m) != Integer(1)) {
        throw std::invalid_argument("Inverse does not exist for these values");
    }
        Integer M = m; // Make a copy of modulus
        Integer A = nonneg_a;
        Integer y = 0, x = 1;
        if (M == 1)
            return 0;
    
        while (A > 1) {
            Integer q = A / M;
            Integer t = M;
            M = A % M; //remainder becomes new divisor
            A = t; //old divisor becomes new dividend
            t = y; // Store old y
            y = x - q * y; // Update y to be the new coefficient
            y = y % m; // Make sure y is positive 
            x = t; // Update x to be the old y
        }
        return x;
    }


// Computes Integral Exponentiation Using Successive Squaring
Integer Integer::power(const Integer& exponent) const {
    if (exponent.isNegative)
        throw std::invalid_argument("Negative exponent not supported");

    Integer result(1);
    Integer base = *this;
    Integer exp = exponent;

    while (exp != Integer(0)) {
        if (exp.getBit(0))
            result *= base;
        base *= base;
        exp >>= 1;
    }

    return result;
}

// Computes
Integer Integer::power_mod(const Integer& exponent, const Integer& modulus) const {
    if (exponent.isNegative)
        throw std::invalid_argument("Negative exponent not supported");
    if (modulus == Integer(0))
        throw std::invalid_argument("Modulus must be non-zero");

    Integer result(1);
    Integer base = *this % modulus;
    Integer exp = exponent;

    while (exp != Integer(0)) {
        if (exp.getBit(0))
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }

    return result;
}
