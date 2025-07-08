#include "Integer.hpp"
#include <algorithm>
#include <stdexcept>

// Bitwise AND
Integer Integer::operator&(const Integer& rhs) const {
    Integer result;
    size_t n = std::min(limbs.size(), rhs.limbs.size());
    result.limbs.resize(n);
    for (size_t i = 0; i < n; ++i)
        result.limbs[i] = limbs[i] & rhs.limbs[i];
    result.normalize();
    return result;
}

// Bitwise OR
Integer Integer::operator|(const Integer& rhs) const {
    Integer result;
    size_t n = std::max(limbs.size(), rhs.limbs.size());
    result.limbs.resize(n);
    for (size_t i = 0; i < n; ++i) {
        uint32_t a = (i < limbs.size()) ? limbs[i] : 0;
        uint32_t b = (i < rhs.limbs.size()) ? rhs.limbs[i] : 0;
        result.limbs[i] = a | b;
    }
    result.normalize();
    return result;
}

// Bitwise XOR
Integer Integer::operator^(const Integer& rhs) const {
    Integer result;
    size_t n = std::max(limbs.size(), rhs.limbs.size());
    result.limbs.resize(n);
    for (size_t i = 0; i < n; ++i) {
        uint32_t a = (i < limbs.size()) ? limbs[i] : 0;
        uint32_t b = (i < rhs.limbs.size()) ? rhs.limbs[i] : 0;
        result.limbs[i] = a ^ b;
    }
    result.normalize();
    return result;
}

// Bitwise NOT (only defined for non-negative values)
Integer Integer::operator~() const {
    if (isNegative)
        throw std::invalid_argument("Bitwise NOT not defined for negative Integer");
    Integer result = *this;
    for (auto& limb : result.limbs)
        limb = ~limb;
    result.normalize();
    return result;
}

// Left shift
Integer Integer::operator<<(int shift) const {
    Integer result = *this;
    result <<= shift;
    return result;
}

Integer& Integer::operator<<=(int shift) {
    if (shift < 0) return *this >>= -shift;
    int limb_shift = shift / 32;
    int bit_shift = shift % 32;

    if (bit_shift == 0) {
        limbs.insert(limbs.begin(), limb_shift, 0);
    } else {
        std::vector<Limb> new_limbs(limb_shift, 0);
        uint64_t carry = 0;
        for (Limb limb : limbs) {
            uint64_t val = (static_cast<uint64_t>(limb) << bit_shift) | carry;
            new_limbs.push_back(static_cast<Limb>(val));
            carry = val >> 32;
        }
        if (carry)
            new_limbs.push_back(static_cast<Limb>(carry));
        limbs = std::move(new_limbs);
    }
    normalize();
    return *this;
}

// Right shift
Integer Integer::operator>>(int shift) const {
    Integer result = *this;
    result >>= shift;
    return result;
}

Integer& Integer::operator>>=(int shift) {
    if (shift < 0) return *this <<= -shift;
    int limb_shift = shift / 32;
    int bit_shift = shift % 32;

    if (limb_shift >= static_cast<int>(limbs.size())) {
        limbs = {0};
        isNegative = false;
        return *this;
    }

    limbs.erase(limbs.begin(), limbs.begin() + limb_shift);
    if (bit_shift == 0) {
        normalize();
        return *this;
    }

    uint64_t carry = 0;
    for (int i = static_cast<int>(limbs.size()) - 1; i >= 0; --i) {
        uint64_t val = (static_cast<uint64_t>(limbs[i]) | (carry << 32)) >> bit_shift;
        carry = limbs[i] & ((1ULL << bit_shift) - 1);
        limbs[i] = static_cast<Limb>(val);
    }
    normalize();
    return *this;
}

void Integer::setBit(int i) {
    if (i < 0) throw std::invalid_argument("Negative bit index");
    size_t limb_index = i / 32;
    size_t bit_index = i % 32;

    if (limb_index >= limbs.size())
        limbs.resize(limb_index + 1, 0);

    limbs[limb_index] |= (1U << bit_index);
    normalize();
}

bool Integer::getBit(int i) const {
    if (i < 0) throw std::invalid_argument("Negative bit index");
    size_t limb_index = i / 32;
    size_t bit_index = i % 32;

    if (limb_index >= limbs.size())
        return false;

    return (limbs[limb_index] >> bit_index) & 1U;
}
