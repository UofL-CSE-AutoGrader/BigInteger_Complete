#include "Integer.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

Integer::Integer() {
    limbs.push_back(0);
}

Integer::Integer(int64_t n) {
    isNegative = (n < 0);
    uint64_t absval = isNegative ? -n : n;
    do {
        limbs.push_back(absval % LIMB_BASE);
        absval /= LIMB_BASE;
    } while (absval > 0);
}

Integer::Integer(const std::string& str) {
    std::string s = str;
    bool negative = false;

    if (!s.empty() && s[0] == '-') {
        negative = true;
        s = s.substr(1);
    }

    if (s.empty() || !std::all_of(s.begin(), s.end(), ::isdigit))
        throw std::invalid_argument("Invalid character in input string");

    *this = Integer(0); // build number from digits
    for (char c : s) {
        *this *= Integer(10);
        *this += Integer(c - '0');
    }
    
    isNegative = negative; // set sign AFTER number is built
    if (*this == Integer(0)) {
        isNegative = false; // zero is not negative
    }
}

