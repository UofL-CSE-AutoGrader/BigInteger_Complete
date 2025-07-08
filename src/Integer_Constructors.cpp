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
    isNegative = false;

    if (!s.empty() && s[0] == '-') {
        isNegative = true;
        s = s.substr(1);
    }

    *this = Integer(0);
    for (char c : s) {
        if (!std::isdigit(c)) throw std::invalid_argument("Invalid character in input string");
        *this *= Integer(10);
        *this += Integer(c - '0');
    }
}

