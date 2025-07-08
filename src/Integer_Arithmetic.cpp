#include "Integer.hpp"
#include <algorithm>
#include <stdexcept>

// Addition assignment
Integer& Integer::operator+=(const Integer& rhs) {
    size_t n = std::max(limbs.size(), rhs.limbs.size());
    limbs.resize(n, 0);

    uint64_t carry = 0;
    for (size_t i = 0; i < n; ++i) {
        uint64_t sum = static_cast<uint64_t>(limbs[i]) +
                       (i < rhs.limbs.size() ? rhs.limbs[i] : 0) + carry;
        limbs[i] = static_cast<Limb>(sum % LIMB_BASE);
        carry = sum / LIMB_BASE;
    }
    if (carry)
        limbs.push_back(static_cast<Limb>(carry));
    normalize();
    return *this;
}

// Subtraction assignment
Integer& Integer::operator-=(const Integer& rhs) {
    if (*this < rhs) {
        Integer temp = rhs;
        temp -= *this;
        *this = temp;
        isNegative = !isNegative;
        return *this;
    }

    uint64_t borrow = 0;
    for (size_t i = 0; i < limbs.size(); ++i) {
        uint64_t a = limbs[i];
        uint64_t b = (i < rhs.limbs.size()) ? rhs.limbs[i] : 0;
        uint64_t diff = LIMB_BASE + a - b - borrow;
        limbs[i] = static_cast<Limb>(diff % LIMB_BASE);
        borrow = (diff < LIMB_BASE) ? 1 : 0;
    }

    normalize();
    return *this;
}

// Multiplication assignment
Integer& Integer::operator*=(const Integer& rhs) {
    std::vector<Limb> result(limbs.size() + rhs.limbs.size(), 0);
    for (size_t i = 0; i < limbs.size(); ++i) {
        uint64_t carry = 0;
        for (size_t j = 0; j < rhs.limbs.size(); ++j) {
            uint64_t product = static_cast<uint64_t>(limbs[i]) * rhs.limbs[j] +
                               result[i + j] + carry;
            result[i + j] = static_cast<Limb>(product % LIMB_BASE);
            carry = product / LIMB_BASE;
        }
        result[i + rhs.limbs.size()] += static_cast<Limb>(carry);
    }

    limbs = std::move(result);
    isNegative = isNegative != rhs.isNegative;
    normalize();
    return *this;
}

// Division assignment (naive long division)
Integer& Integer::operator/=(const Integer& rhs) {
    if (rhs == Integer(0))
        throw std::invalid_argument("Division by zero");

    Integer dividend = *this;
    Integer divisor = rhs;
    dividend.isNegative = false;
    divisor.isNegative = false;

    if (dividend < divisor) {
        *this = Integer(0);
        return *this;
    }

    Integer quotient(0);
    Integer remainder(0);

    for (int i = dividend.limbs.size() * 32 - 1; i >= 0; --i) {
        remainder <<= 1;
        if ((dividend.limbs[i / 32] >> (i % 32)) & 1)
            remainder += Integer(1);

        if (remainder >= divisor) {
            remainder -= divisor;
            quotient.setBit(i);
        }
    }

    quotient.isNegative = isNegative != rhs.isNegative;
    *this = quotient;
    normalize();
    return *this;
}

Integer& Integer::operator%=(const Integer& rhs) {
    if (rhs == Integer(0))
        throw std::invalid_argument("Division by zero");
    if (*this < Integer(0)) {
        *this = rhs - ((-*this)%rhs); // Ensure positive remainder
    }
    Integer quotient = *this / rhs;
    *this -= quotient * rhs;

    // Normalize to range [0, |rhs|)
    if (isNegative) {
        if (rhs.isNegative)
            *this -= rhs;
        else
            *this += rhs;
    }

    return *this;
}



// Binary operators
Integer Integer::operator+(const Integer& rhs) const {
    Integer result = *this;
    result += rhs;
    return result;
}

Integer Integer::operator-(const Integer& rhs) const {
    Integer result = *this;
    result -= rhs;
    return result;
}

Integer Integer::operator*(const Integer& rhs) const {
    Integer result = *this;
    result *= rhs;
    return result;
}

Integer Integer::operator/(const Integer& rhs) const {
    Integer result = *this;
    result /= rhs;
    return result;
}

Integer Integer::operator%(const Integer& rhs) const {
    Integer result = *this;
    result %= rhs;
    return result;
}


// Pre-increment (++x)
Integer& Integer::operator++() {
    *this += Integer(1);
    return *this;
}

// Post-increment (x++)
Integer Integer::operator++(int) {
    Integer temp = *this;
    ++(*this);
    return temp;
}

// Pre-decrement (--x)
Integer& Integer::operator--() {
    *this -= Integer(1);
    return *this;
}

// Post-decrement (x--)
Integer Integer::operator--(int) {
    Integer temp = *this;
    --(*this);
    return temp;
}

Integer Integer::operator-() const {
    Integer result = *this;
    if (result != Integer(0)) {
        result.isNegative = !result.isNegative;
    }
    return result;
}