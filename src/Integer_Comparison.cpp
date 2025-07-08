#include "Integer.hpp"

// Equality
bool Integer::operator==(const Integer& rhs) const {
    return isNegative == rhs.isNegative && limbs == rhs.limbs;
}

bool Integer::operator!=(const Integer& rhs) const {
    return !(*this == rhs);
}

// Less than
bool Integer::operator<(const Integer& rhs) const {
    if (isNegative != rhs.isNegative)
        return isNegative;

    if (limbs.size() != rhs.limbs.size())
        return isNegative ? (limbs.size() > rhs.limbs.size())
                          : (limbs.size() < rhs.limbs.size());

    for (size_t i = limbs.size(); i-- > 0; ) {
        if (limbs[i] != rhs.limbs[i])
            return isNegative ? (limbs[i] > rhs.limbs[i])
                              : (limbs[i] < rhs.limbs[i]);
    }

    return false;
}

// Less than or equal
bool Integer::operator<=(const Integer& rhs) const {
    return *this < rhs || *this == rhs;
}

// Greater than
bool Integer::operator>(const Integer& rhs) const {
    return !(*this <= rhs);
}

// Greater than or equal
bool Integer::operator>=(const Integer& rhs) const {
    return !(*this < rhs);
}
